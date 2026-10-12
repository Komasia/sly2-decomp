struct S { char pad[0x394]; int n; int a[1]; };
void *func_002332B8(void *d, void *s, int n);
void func_00208728(struct S *p, int x)
{
    int i;
    for (i = 0; i < p->n; i++) {
        if (p->a[i] == x) {
            func_002332B8(p->a + i, p->a + i + 1, (p->n - i) * 4 - 4);
            p->n--;
        }
    }
}
