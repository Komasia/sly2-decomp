#include "stepguard.h"
#include "vtbl.h"
/* a noise: its kind-4 target, kind, and the next live noise */
struct NOISE { char pad[0x44]; int ploTarget; char pad2[0x54 - 0x48]; int nKind; struct NOISE *pnoiseNext; };
/* a detector entry: its state at +0x4 */
struct DETENTRY { int unk_0x00; int st; };
extern struct { char pad[0x148C]; struct NOISE *pnoiseFirst; } D_003E0000;   /* the live noises (D_003E148C) */
extern float g_clock;   /* g_clock.t */
extern float D_002C3DB0;   /* the response cooldown */
int FGuardFreeN__FP5GUARD(struct GUARD *pguard);
int NCompareNoises__FP5GUARDP5NOISET1(struct GUARD *pguard, struct NOISE *pnoiseA, struct NOISE *pnoiseB);
struct DETENTRY *PdetentryFind__FP8DETECTORi(void *pdet, int plo);
void SetDetentryState__FP8DETECTORP8DETENTRYi(void *pdet, struct DETENTRY *pdetentry, int st);

/* PloGuardInterest (0x20A408): the noise that interests a free guard most (vt slot 89 accepts it, NCompareNoises
 * orders them), else pnoiseDefault. A kind-4 noise about one of its detector entries instead wakes that entry
 * (state 2, with the response cooldown) and gives pnoiseDefault. */
// name: SafeHouse port (PloGuardInterest)
struct NOISE *PloGuardInterest__FP5GUARDP2LO(struct GUARD *pguard, struct NOISE *pnoiseDefault)
{
    struct NOISE *pnoise, *pnoiseBest;
    int unused[4];
    if (!FGuardFreeN__FP5GUARD(pguard))
        return pnoiseDefault;
    pnoiseBest = pnoiseDefault;
    for (pnoise = D_003E0000.pnoiseFirst; pnoise; pnoise = pnoise->pnoiseNext) {
        if (((int (*)(void *, struct NOISE *))pguard->step.po.so.lo.pvt[89].pfn)(VT_THIS(pguard, &pguard->step.po.so.lo.pvt[89]), pnoise)) {
            if (!pnoiseBest || NCompareNoises__FP5GUARDP5NOISET1(pguard, pnoise, pnoiseBest) < 0)
                pnoiseBest = pnoise;
        }
    }
    if (pnoiseBest && pnoiseBest->nKind == 4) {
        struct DETENTRY *pdetentry = PdetentryFind__FP8DETECTORi(pguard->pdet, pnoiseBest->ploTarget);
        if (pdetentry) {
            if (!pdetentry->st) {
                SetDetentryState__FP8DETECTORP8DETENTRYi(pguard->pdet, pdetentry, 2);
                pguard->tNextAction = g_clock + D_002C3DB0;
            }
            return pnoiseDefault;
        }
    }
    return pnoiseBest;
}
