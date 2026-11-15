/* func_00205588 (0x205588): PO/STEP vt slot 84: releases the effects in grfEffect: the last release of each
 * retracts its effect SM on the object. */
#include "step.h"
extern char D_003DD040[];   /* the effect SM oid table (D_002C3C40: 1548 1549 1550 - 1551 1552) */
/* the STEP fields used here */
#define CEFFECT_STEP 6
#define FSO_FindNearest 4   /* GRFFSO find mode: the nearest object with the oid (Sly 1 so.h FSO_FindNearest) */
int func_001FD0C0(void *ptable, int ieffect);   /* the effect's SM oid */
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int grffso, int oid, struct STEP *ploNear);
void *PsmaFindSm(void *psm, struct STEP *palo) asm("PsmaFindSm__FP2SMP3ALO");
void RetractSma__FP3SMA(void *psma);
void func_00205588(struct STEP *pstep, int grfEffect)
{
    int ieffect;
    for (ieffect = 0; ieffect < CEFFECT_STEP; ieffect++) {
        int fValid = (unsigned int)ieffect < CEFFECT_STEP;
        int grf = 1 << ieffect;
        if (!fValid) grf = 0;
        if (grfEffect & grf) {
            if (pstep->acHoldEffect[ieffect] != 0) {
                if (--pstep->acHoldEffect[ieffect] <= 0) {
                    int oid = func_001FD0C0(D_003DD040, ieffect);
                    void *psm = PloFindSwNearest__FP2LO3OIDii(&g_sw, FSO_FindNearest, oid, pstep);
                    if (psm) {
                        void *psma = PsmaFindSm(psm, pstep);
                        if (psma)
                            RetractSma__FP3SMA(psma);
                    }
                }
            }
        }
    }
}
