/* Resets a constraint system's solution: every row's g and residual to 0 and every row back in the open list. */
#include "dzg.h"

extern "C" {
void ClearDl(DL *pdl) asm("ClearDl__FP2DL");
void ClearDle(DLE *pdle) asm("ClearDle__FP3DLE");
void AppendDlEntry(DL *pdl, void *pv) asm("AppendDlEntry__FP2DLPv");
}

void ClearDzgSolution(DZG *pdzg)
{
    int i;

    pdzg->cdzClamped = 0;
    ClearDl(&pdzg->dlClamped);
    ClearDl(&pdzg->dlLower);
    ClearDl(&pdzg->dlUpper);
    ClearDl(&pdzg->dlOpen);

    for (i = 0; i < pdzg->cdz; i++) {
        DZ *pdz = &pdzg->adz[i];
        pdz->g = pdz->gResidual = 0.0f;
        ClearDle(&pdz->dle);
        AppendDlEntry(&pdzg->dlOpen, pdz);
    }
}
