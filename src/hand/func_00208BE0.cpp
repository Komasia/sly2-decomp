typedef int qword __attribute__((mode(TI)));
struct LOF { char pad[0x28]; unsigned long grfLo; };
struct NOISETMPL { char pad[0x50]; int nType; };
struct DETECTOR { char pad[0xE8]; LOF *ploVolume; };
struct NOISE;
struct GUARD { char pad[0xEC]; void *poxa; char pad2[0xE68 - 0xF0]; int nE68; char pad3[0xF64 - 0xE6C]; DETECTOR *pdet; };
/* a noise (an LO): its template, place, owner, kind-4 target and kind */
struct NOISE { char pad[0x14]; NOISETMPL *ptmpl; char pad1[0x20 - 0x18]; qword posNoise; char pad2[0x40 - 0x30]; GUARD *ploOwner; void *ploTarget; char pad3[0x54 - 0x48]; int nKind; };
extern "C" {
int FGuardFreeN(GUARD *pguard) asm("FGuardFreeN__FP5GUARD");
void *PdetentryFind(DETECTOR *pdet, void *plo) asm("PdetentryFind__FP8DETECTORi");
qword PosOfLo(void *plo) asm("PosOfLo__FP2LO");
int FNoiseReaches(NOISE *pnoise, qword pos) asm("FNoiseReaches__FP5NOISEG9VU_VECTOR");
int FPointInShape(LOF *plo, qword pos) asm("FPointInShape__FP2LOG9VU_VECTOR");
void func_0020FAA0(void *psw, qword posFrom, qword posTo, void *pfnFilter, void *pvFilter, int *pcso, int *papso);   /* the objects near a line */
int PsoHitTestLineObjects(int grf, qword posFrom, qword posTo, int cso, int apso, void *plsg) asm("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
void func_0020FA10();
extern char g_sw[];
int FGuardAcceptsNoise(GUARD *pguard, NOISE *pnoise) asm("FGuardAcceptsNoise__FP5GUARDP5NOISE");
}
class FRAME { public: FRAME(); ~FRAME(); };

/* FGuardAcceptsNoise (0x208BE0): whether the guard takes a noise: it must be free, the noise at least its kind
 * threshold nE68, not its own, and a kind-4 noise about it or one of its detector entries; then a heard noise
 * (template type 0) must reach it, and a seen one (type 1) be inside its detector's live view volume with nothing
 * solid between. Field names: SafeHouse port (ainoise.h NOISE). */
// name: SafeHouse port (FGuardAcceptsNoise)
int FGuardAcceptsNoise(GUARD *pguard, NOISE *pnoise)
{
    int nType;
    NOISETMPL *ptmpl;
    qword posGuard, posNoise;
    if (!FGuardFreeN(pguard))
        return 0;
    if (pnoise->nKind < pguard->nE68)
        return 0;
    if (pnoise->ploOwner && pnoise->ploOwner == pguard)
        return 0;
    if (pnoise->nKind == 4) {
        void *ploTarget = pnoise->ploTarget;
        void *pdetentry = PdetentryFind(pguard->pdet, ploTarget);
        if (ploTarget != pguard && !pdetentry)
            return 0;
    }
    ptmpl = pnoise->ptmpl;
    posGuard = PosOfLo(pguard);
    posNoise = pnoise->posNoise;
    switch (ptmpl->nType) {
    case 0:
        return FNoiseReaches(pnoise, PosOfLo(pguard));
    case 1: {
        LOF *ploVolume = pguard->pdet->ploVolume;
        if (!ploVolume || ((ploVolume->grfLo >> 60) & 1) == 0)
            return 0;
        if (!FPointInShape(ploVolume, posNoise))
            return 0;
        {
            FRAME frame;
            int i, j;
            func_0020FAA0(g_sw, posGuard, posNoise, (void *)func_0020FA10, pguard->poxa, &i, &j);
            if (!PsoHitTestLineObjects(0, posGuard, posNoise, i, j, 0))
                return 1;
            return 0;
        }
    }
    }
    return 0;
}
