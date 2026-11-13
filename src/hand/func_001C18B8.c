struct E { int x0; unsigned short x4; unsigned short x6; };
void CopyAb(void *dst, void *src, int cb) asm("CopyAb__FPvT0Ui");
void func_001C18B8(int n, struct E *a, int key)
{
    int i, iFirst, iLast;
    struct E *pe;
    i = 0;
    pe = a;
    goto test;
    for (;;) {
        pe++;
        i++;
    test:
        if (i >= n) break;
        if (pe->x6 == key) {
            if (pe->x4 != 0) {
                iFirst = i;
                continue;
            }
            iLast = i;
            break;
        }
    }
    CopyAb(&a[iFirst], &a[iFirst] + 1, (iLast - iFirst - 1) * sizeof(struct E));
    CopyAb(&a[iLast] - 1, &a[iLast] + 1, (n - iLast - 1) * sizeof(struct E));
}
