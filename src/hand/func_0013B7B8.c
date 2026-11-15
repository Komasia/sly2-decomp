/* Sorts the c ints an (qsort with 0x13B7A0) and drops the repeated ones (*pc becomes the count left). */
void qsort(void *, int, int, int (*)(const void *, const void *));
int func_0013B7A0(const void *, const void *);
void func_0013B7B8(void *unused, int *pc, int *an) {
    int n = *pc;
    int *pDst, *pSrc, *pMax;
    if (n < 2) return;
    qsort(an, n, 4, func_0013B7A0);
    pDst = an;
    pMax = an + n;
    for (pSrc = an; pSrc < pMax; pSrc++) {
        if (*pDst != *pSrc) *++pDst = *pSrc;
    }
    *pc = pDst - an + 1;
}
