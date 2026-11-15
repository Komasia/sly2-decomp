#include "dl.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

extern DLI *s_pdliFirst;

void RemoveDlEntry__FP2DLPv(DL *pdl, void *pv)
{
    DLE *pdle = PDLE(pdl, pv);
    DLI *pdli = s_pdliFirst;
    void *pvT;

    while (pdli) {
        if ((DLE *)pdli->ppv == pdle) {
            void *pvPrev = pdle->prev;
            if (pvPrev) {
                pdli->ppv = (void **)PDLE(pdl, pvPrev);
            } else {
                pdli->ppv = (void **)pdl;
            }
        }
        pdli = pdli->pdliNext;
    }

    pvT = pdle->prev;
    if (pvT) {
        PDLE(pdl, pvT)->next = pdle->next;
    } else {
        pdl->head = pdle->next;
    }

    pvT = pdle->next;
    if (pvT) {
        PDLE(pdl, pvT)->prev = pdle->prev;
    } else {
        pdl->tail = pdle->prev;
    }

    pdle->next = 0;
    pdle->prev = 0;
}
