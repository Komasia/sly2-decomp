typedef int qword __attribute__((mode(TI)));
struct SEGMARK { float a; float b; };
struct SEGMARKREF { int a; int b; struct SEGMARK *pz; };
struct ASEGA { char pad[0x18]; void *palo; float tLocal; };
struct ASEGBLG { char pad[0x50]; struct ASEGA *pasega; char pad2[0x74 - 0x54]; float tLoop; char pad3[0xD0 - 0x78]; struct SEGMARKREF *amrsg; };
struct GAIT { int pad0; struct ASEGBLG *pasegbl; char pad1[0x50 - 8]; float uMix; char pad2[0x90 - 0x54]; int sfx; float gVolLo; float gVolHi; int afFoot[2]; };
float GModPositive__Fff(float g, float gMod);
void *PsndNewPlain__Fi(int sfx);
void SetSource__4CSndPv(void *psnd, void *pvSource);
qword PosOfLo__FP2LO(void *plo);
void SetPosition__4CSndG9VU_VECTOR(void *psnd, qword pos);
void SetFalloff__4CSndff(void *psnd, float sNear, float sFar);
void SetVolume__4CSndf(void *psnd, float uVol);

/* UpdateGaitFeet (0x20BC08): each foot's marker segment state from the blend's clip time; when a foot wraps, a
 * footstep sound at the actor, its volume between gVolLo and gVolHi by the mix. Field names: SafeHouse port. */
// name: SafeHouse port (UpdateGaitFeet)
void UpdateGaitFeet__FP4GAIT(struct GAIT *pgait)
{
    struct ASEGA *pasega = pgait->pasegbl->pasega;
    float tLocal = pasega->tLocal;
    int i;
    for (i = 0; i < 2; i++) {
        struct ASEGBLG *pasegbl = pgait->pasegbl;
        struct SEGMARK *pmark = pasegbl->amrsg[i].pz;
        int fPast = pmark->b <= GModPositive__Fff(tLocal - pmark->a, pasegbl->tLoop);
        if (fPast == pgait->afFoot[i])
            continue;
        if (!fPast) {
            float uVol = pgait->uMix;
            void *psnd;
            { float u = 1.0f - uVol; uVol *= pgait->gVolHi; uVol += u * pgait->gVolLo; }
            psnd = PsndNewPlain__Fi(pgait->sfx);
            SetSource__4CSndPv(psnd, 0);
            SetPosition__4CSndG9VU_VECTOR(psnd, PosOfLo__FP2LO(pasega->palo));
            SetFalloff__4CSndff(psnd, 500.0f, 2000.0f);
            SetVolume__4CSndf(psnd, uVol);
        }
        pgait->afFoot[i] = fPast;
    }
}
