typedef struct QW { int a[4]; } QW;
void func_0020FFF0(void *p, QW *pq, int a, int b, int c, int d);
// name: SafeHouse port (ApplyRsmg)
void ApplyRsmg__FP2LOiP4RSMGii(void *p, int c, QW *pq, int a, int b)
{
    int i;
    for (i = 0; i < c; i++) {
        func_0020FFF0(p, &pq[i], a, b, 0, 0);

    }
}
