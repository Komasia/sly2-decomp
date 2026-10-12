typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLE { void *pvNext; void *pvPrev; } DLE;
typedef struct DLI { DL *pdl; void **ppv; int ibDle; struct DLI *pdliNext; } DLI;
#define PDLE(pdl, pv) ((DLE *)((char *)(pv) + (pdl)->ibDle))

void func_0011A220(DL *pdl, void *pv);
void func_0011A250(DL *pdl, void *pv);

void func_0011A280(DL *pdl, void *pvNext, void *pv)
{
    if (!pvNext) {
        func_0011A220(pdl, pv);
    } else if (pvNext == pdl->pvFirst) {
        func_0011A250(pdl, pv);
    } else {
        DLE *pdle = PDLE(pdl, pv);
        DLE *pdleNext = PDLE(pdl, pvNext);
        void *pvPrev = pdleNext->pvPrev;
        DLE *pdlePrev = PDLE(pdl, pvPrev);
        pdle->pvNext = pvNext;
        pdle->pvPrev = pvPrev;
        pdleNext->pvPrev = pv;
        pdlePrev->pvNext = pv;
    }
}
