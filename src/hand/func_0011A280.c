#include "dl.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
void PrependDlEntry__FP2DLPv(DL *pdl, void *pv);

void InsertDlEntryBefore__FP2DLPvT1(DL *pdl, void *pvNext, void *pv)
{
    if (!pvNext) {
        AppendDlEntry__FP2DLPv(pdl, pv);
    } else if (pvNext == pdl->head) {
        PrependDlEntry__FP2DLPv(pdl, pv);
    } else {
        DLE *pdle = PDLE(pdl, pv);
        DLE *pdleNext = PDLE(pdl, pvNext);
        void *pvPrev = pdleNext->prev;
        DLE *pdlePrev = PDLE(pdl, pvPrev);
        pdle->next = pvNext;
        pdle->prev = pvPrev;
        pdleNext->prev = pv;
        pdlePrev->next = pv;
    }
}
