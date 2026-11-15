/* A small LCP: c rows with the couplings agA (c x c, row-major) and the residuals agB; solves for agX
 * (each at most g) with a stack-allocated constraint system. */
#define DZG_ROWS_ONLY
#include "dzg.h"
typedef struct MSG { int cb; int nKind; } MSG;
typedef struct FRAME { int an[4]; } FRAME;

void __10STACKSCOPE(FRAME *pframe);
void _$_10STACKSCOPE(FRAME *pframe, int n);
void *PvAllocStackImpl__Fi(MSG *pmsg);
void CopyAb(void *pvDst, void *pvSrc, unsigned int cb) asm("CopyAb__FPvT0Ui");
DZG *InitDzgRows__FP3DZGi(DZG *pdzg, int cdzMax);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
void EnforceDzgConstraints__FP3DZG(DZG *pdzg);

static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocStackImpl__Fi(pmsg); }
// name: SafeHouse port (SolveDzgConstraints)
void SolveDzgConstraints__FiPfN21f(int c, float *agA, float *agB, float *agX, float g)
{
    FRAME frame;
    DZG dzg;
    MSG msg;
    int i;

    __10STACKSCOPE(&frame);
    InitDzgRows__FP3DZGi(&dzg, c);
    for (i = 0; i < c; i++) {
        DZ *pdz = &dzg.adz[i];
        pdz->gMax = g;
        pdz->agCoupling = (float *)PvAllocMsg(&msg, c * sizeof(float), 0x10);
        CopyAb(pdz->agCoupling, agA + i * c, c * sizeof(float));
        pdz->gResidual = agB[i];
        AppendDlEntry__FP2DLPv(&dzg.dlOpen, pdz);
    }
    dzg.cdz = c;
    EnforceDzgConstraints__FP3DZG(&dzg);
    for (i = 0; i < c; i++) {
        agX[i] = dzg.adz[i].g;
    }
    _$_10STACKSCOPE(&frame, 2);
}
