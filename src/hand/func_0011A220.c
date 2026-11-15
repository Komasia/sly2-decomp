/* Doubly-linked list: appends pv at the tail. */
#include "dl.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

void AppendDlEntry__FP2DLPv(DL *pdl, void *pv)
{
    DLE *pdle = PDLE(pdl, pv);
    if (!pdl->tail) {
        pdl->tail = pv;
        pdl->head = pv;
    } else {
        DLE *pdleLast = PDLE(pdl, pdl->tail);
        pdle->prev = pdl->tail;
        pdleLast->next = pv;
        pdl->tail = pv;
    }
}
