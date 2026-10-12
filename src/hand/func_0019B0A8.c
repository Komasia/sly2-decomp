struct SO { char pad[0x70]; long fl; };
struct A { char pad[0xEC]; struct SO *pso; };
struct X { int a; struct A *pa; int b, c; long fl; };
struct L { int c; struct SO **a; };
int func_0019B0A8(struct L *l, struct X *x) {
    struct SO *pso;
    int i;
    if (x->fl & (1L << 48)) return 0;
    pso = x->pa->pso;
    if (pso->fl & 4) return 0;
    for (i = 0; i < l->c; i++) if (pso == l->a[i]) return 0;
    return 1;
}
