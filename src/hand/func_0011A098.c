typedef struct SL { void *pvFirst; void *pvLast; int ibNext; } SL;

void func_0011A098(SL *psl, void *pv)
{
    void **ppvNext = (void **)((char *)pv + psl->ibNext);
    if (psl->pvFirst == 0) {
        psl->pvLast = pv;
        psl->pvFirst = pv;
    } else {
        *ppvNext = psl->pvFirst;
        psl->pvFirst = pv;
    }
}
