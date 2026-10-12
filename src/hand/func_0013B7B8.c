void func_002338C0(void *, int, int, int (*)(const void *, const void *));
int func_0013B7A0(const void *, const void *);
void func_0013B7B8(void *unused, int *pc, int *a) {
    int n = *pc;
    int *pDst, *pSrc, *pMax;
    if (n < 2) return;
    func_002338C0(a, n, 4, func_0013B7A0);
    pDst = a;
    pMax = a + n;
    for (pSrc = a; pSrc < pMax; pSrc++) {
        if (*pDst != *pSrc) *++pDst = *pSrc;
    }
    *pc = pDst - a + 1;
}
