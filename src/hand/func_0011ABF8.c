/* Solves the rows of a constraint system: the two-sided rows clamped first, then the open row with the most
 * negative residual (below -0.01) enforced until none is left. */
#include "dzg.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; int nUnused; } DLI;


extern DLI *s_pdliFirst;
void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
void EnforceDzgDz(DZG *pdzg, DZ *pdz) asm("EnforceDzgDz__FP3DZGP2DZ");

static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->pdl = pdl;
    pdli->ppv = (void **)pdl;
    pdli->ibDle = pdl->ibDle;
    pdli->pdliNext = s_pdliFirst;
    s_pdliFirst = pdli;
}

static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->ppv;
    pdli->ppv = (void **)((char *)pv + pdli->ibDle);
    return pv;
}

// name: SafeHouse port (EnforceDzgConstraints)
void EnforceDzgConstraints__FP3DZG(DZG *pdzg)
{
    DLI dli;
    DZ *pdz;

    InitDli(&dli, &pdzg->dlOpen);
    while ((pdz = (DZ *)PvNextDli(&dli)) != 0) {
        if (pdz->kind == DZK_TwoSided) {
            RemoveDlEntry__FP2DLPv(&pdzg->dlOpen, pdz);
            AppendDlEntry__FP2DLPv(&pdzg->dlClamped, pdz);
            pdzg->cdzClamped++;
        }
    }
    EnforceDzgDz(pdzg, 0);
    s_pdliFirst = dli.pdliNext;

    for (;;) {
        DZ *pdzMin = 0;
        float gMin = -0.01f;
        DZ *pdzT;
        for (pdzT = (DZ *)pdzg->dlOpen.head; pdzT; pdzT = (DZ *)pdzT->dle.next) {
            if (pdzT->gResidual < gMin) {
                gMin = pdzT->gResidual;
                pdzMin = pdzT;
            }
        }
        if (!pdzMin) {
            break;
        }
        EnforceDzgDz(pdzg, pdzMin);
    }
}
