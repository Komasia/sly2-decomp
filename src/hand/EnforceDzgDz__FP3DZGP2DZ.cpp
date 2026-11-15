// EnforceDzgDz: Sly 1's dzg solver step (A/B/C/D constraint lists, Crout decomposition).
/* One LCP pivoting pass (at most 10 steps): adds pdz (if any) to the clamped set, solves the clamped system and
 * moves the row that first hits a bound (or leaves one) between the clamped, lower and upper lists. */
#include "dzg.h"

extern "C" {
void AppendDlEntry(DL *pdl, void *pv) asm("AppendDlEntry__FP2DLPv");
void RemoveDlEntry(DL *pdl, void *pv) asm("RemoveDlEntry__FP2DLPv");
extern const float D_002A4120;
extern const float D_002A4124;
}
void CroutDecomp(int n, float *a, float *lu);
void CroutSolve(int n, float *lu, float *b, float *x);

void EnforceDzgDz(DZG *pdzg, DZ *pdz)
{
    int iter;
    if (pdz) {
        RemoveDlEntry(&pdzg->dlOpen, pdz);
        AppendDlEntry(&pdzg->dlClamped, pdz);
        pdzg->cdzClamped++;
    }
    for (iter = 0; iter < 10; iter++) {
        DZ *pdzI, *pdzJ, *pdzK, *pdzBest;
        float *pg;
        int i, k;
        float gMin;

        float *pgA = pdzg->agA;
        for (pdzI = (DZ *)pdzg->dlClamped.head; pdzI; pdzI = (DZ *)pdzI->dle.next)
            for (pdzJ = (DZ *)pdzg->dlClamped.head; pdzJ; pdzJ = (DZ *)pdzJ->dle.next)
                *pgA++ = pdzI->agCoupling[pdzJ - pdzg->adz];
        CroutDecomp(pdzg->cdzClamped, pdzg->agA, pdzg->agLu);
        float *pgB = pdzg->agB;
        for (pdzI = (DZ *)pdzg->dlClamped.head; pdzI; pdzI = (DZ *)pdzI->dle.next)
            *pgB++ = -pdzI->gResidual;
        CroutSolve(pdzg->cdzClamped, pdzg->agLu, pdzg->agB, pdzg->agX);
        for (i = 0; i < pdzg->cdz; i++) {
            float g = 0.0f;
            float *pgX = pdzg->agX;
            for (pdzI = (DZ *)pdzg->dlClamped.head; pdzI; pdzI = (DZ *)pdzI->dle.next)
                g += *pgX++ * pdzI->agCoupling[i];
            pdzg->adz[i].dgResidual = g;
        }

        pdzBest = 0;
        gMin = 1.0f;
        k = 0;
        pg = pdzg->agX;
        for (pdzI = (DZ *)pdzg->dlClamped.head; pdzI; pdzI = (DZ *)pdzI->dle.next) {
            float x = *pg++;
            if (x > 1e-4f) {
                // Empty asm, allocation-only operands (emits nothing): two extra uses of the +-1e-4 constants
                // raise their global-alloc priority above the hoisted D_002A4120/D_002A4124 loads, whose
                // REG_EQUIV-less pseudos otherwise win (local-alloc doubles the constants' live length), so
                // the constants get f5/f4 and the globals f7/f6 as in the target.
                __asm__("" : : "f"(1e-4f), "f"(-1e-4f));
                if (pdzI->gMax != D_002A4120) {
                    float t = (pdzI->gMax - pdzI->g) / x;
                    if (t < gMin) {
                        gMin = t;
                        pdzBest = pdzI;
                        k = 4;
                    }
                }
            } else if (x < -1e-4f) {
                if (pdzI->gMin != D_002A4124) {
                    float t = (pdzI->gMin - pdzI->g) / x;
                    if (t < gMin) {
                        gMin = t;
                        pdzBest = pdzI;
                        k = 2;
                    }
                }
            }
        }
        for (pdzK = (DZ *)pdzg->dlLower.head; pdzK; pdzK = (DZ *)pdzK->dle.next) {
            if (pdzK->dgResidual > -1e-4f) {} else {
                float t = -pdzK->gResidual / pdzK->dgResidual;
                if (t < gMin) {
                    gMin = t;
                    pdzBest = pdzK;
                    k = 1;
                }
            }
        }
        for (pdzK = (DZ *)pdzg->dlUpper.head; pdzK; pdzK = (DZ *)pdzK->dle.next) {
            if (pdzK->dgResidual < 1e-4f) {} else {
                float t = -pdzK->gResidual / pdzK->dgResidual;
                if (t < gMin) {
                    gMin = t;
                    pdzBest = pdzK;
                    k = 3;
                }
            }
        }
        for (i = 0; i < pdzg->cdz; i++) {
            DZ *pdzT = &pdzg->adz[i];
            pdzT->gResidual += gMin * pdzT->dgResidual;
        }
        pg = pdzg->agX;
        for (pdzI = (DZ *)pdzg->dlClamped.head; pdzI; pdzI = (DZ *)pdzI->dle.next)
            pdzI->g += gMin * *pg++;

        switch (k) {
        case 0:
            return;
        case 2:
            pdzg->cdzClamped--;
            RemoveDlEntry(&pdzg->dlClamped, pdzBest);
            AppendDlEntry(&pdzg->dlLower, pdzBest);
            if (pdzBest == pdz)
                return;
            break;
        case 1:
            pdzg->cdzClamped++;
            RemoveDlEntry(&pdzg->dlLower, pdzBest);
            AppendDlEntry(&pdzg->dlClamped, pdzBest);
            break;
        case 4:
            pdzg->cdzClamped--;
            RemoveDlEntry(&pdzg->dlClamped, pdzBest);
            AppendDlEntry(&pdzg->dlUpper, pdzBest);
            if (pdzBest == pdz)
                return;
            break;
        case 3:
            pdzg->cdzClamped++;
            RemoveDlEntry(&pdzg->dlUpper, pdzBest);
            AppendDlEntry(&pdzg->dlClamped, pdzBest);
            break;
        }
    }
}
