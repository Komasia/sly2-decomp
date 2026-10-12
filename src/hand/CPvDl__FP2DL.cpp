typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLE { void *pvNext; void *pvPrev; } DLE;
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

int CPvDl(DL *pdl)
{
    void *pv = pdl->pvFirst;
    int c = 0;
    while (pv) {
        pv = PDLE(pdl, pv)->pvNext;
        c++;
    }
    return c;
}
