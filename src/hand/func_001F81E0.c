struct A { char pad[0xAC]; int c; int *a; int n; };
void func_001F81E0(struct A *p, int n)
{
    int i;
    if (n == -1) {
        p->n = 0;
        return;
    }
    for (i = 0; i < p->c; i++) {
        if (n == p->a[i]) {
            p->n = -(i + 3);
            return;
        }
    }
    p->n = 0;
}
