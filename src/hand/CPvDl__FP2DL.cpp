#include "dl.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

int CPvDl(DL *pdl)
{
    void *pv = pdl->head;
    int c = 0;
    while (pv) {
        pv = PDLE(pdl, pv)->next;
        c++;
    }
    return c;
}
