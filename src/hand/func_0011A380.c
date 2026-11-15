#include "dl.h"
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

int FFindDlEntry__FP2DLPv(DL *pdl, void *pv)
{
    return PDLE(pdl, pv)->next || pdl->tail == pv;
}
