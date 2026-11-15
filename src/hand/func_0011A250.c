#include "dl.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

void PrependDlEntry__FP2DLPv(DL *pdl, void *pv)
{
    DLE *pdle = PDLE(pdl, pv);
    if (!pdl->head) {
        pdl->tail = pv;
        pdl->head = pv;
    } else {
        DLE *pdleFirst = PDLE(pdl, pdl->head);
        pdle->next = pdl->head;
        pdleFirst->prev = pv;
        pdl->head = pv;
    }
}
