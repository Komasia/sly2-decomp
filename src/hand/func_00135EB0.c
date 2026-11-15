/* UpdateActorSupport (Bentley's): on the ground states the support (+0x208) is recorded as safe ground when its +0x88 is
 * over 0.7, its object is not flagged 0x20000000 and +0x108C is clear; the interaction's / pipe's
 * own safe points otherwise. */
typedef int ti128 __attribute__((mode(TI)));
struct SO { char pad[0x148]; unsigned long grf; };
struct SUPPORT { char pad[0x40]; int psoe; char pad1[8]; struct SO *pso; char pad2[0x60 - 0x50]; ti128 pos; char pad3[0x88 - 0x70]; float g88; };
struct BENTLEY { char pad[0x208]; struct SUPPORT *psup; char pad1[0x4c0 - 0x20c]; int interact; char pad2[0x9e0 - 0x4c4]; int safe;
    char pad3[0xf50 - 0x9e4]; int climb; char pad4[0x108c - 0xf54]; int n108C; char pad5[0x13d0 - 0x1090]; int state; };
void RecordSafeGround__FP5ACTORP3SOEG9VU_VECTOR(void *, int, ti128);
void UpdateSafeInteract__FP5ACTOR(void *);
void UpdateSafePipe__FP5ACTOR(void *);
// name: SafeHouse port (UpdateActorSupport)
void UpdateActorSupport__FP5ACTOR(struct BENTLEY *pbentley) {
    struct SUPPORT *psup;
    switch (pbentley->state) {
    case 0: case 1: case 5: case 6: case 7: case 11: case 12: case 14:
        psup = pbentley->psup;
        if (psup && 0.7f < psup->g88 && !(psup->pso->grf & 0x20000000) && !pbentley->n108C)
            RecordSafeGround__FP5ACTORP3SOEG9VU_VECTOR(&pbentley->safe, psup->psoe, psup->pos);
        break;
    case 3:
        UpdateSafeInteract__FP5ACTOR(&pbentley->interact);
        break;
    case 13:
        UpdateSafePipe__FP5ACTOR(&pbentley->climb);
        break;
    }
}
