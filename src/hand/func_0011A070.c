typedef struct SL { void *pvFirst; void *pvLast; int ibNext; } SL;

void func_0011A070(SL *psl, void *pv)
{
    if (psl->pvLast == 0) {
        psl->pvLast = pv;
        psl->pvFirst = pv;
    } else {
        *(void **)((char *)psl->pvLast + psl->ibNext) = pv;
        psl->pvLast = pv;
    }
}
