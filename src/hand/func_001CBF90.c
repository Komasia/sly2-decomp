struct S { char pad[0x1010]; int n; };
struct G { char pad[0x600]; int a; };
extern struct G D_002DDF40;
extern int D_002F7900;
void func_0014E328(struct G *pg, int n, void *pv, int m, void *p);
void func_0014E4C8(struct G *pg, int a, int b, void *c, void *d, int e);
void func_001CBF90(struct S *p, int n)
{
    if (p->n == n) return;
    p->n = n;
    if (n) func_0014E328(&D_002DDF40, 6, &D_002DDF40.a, D_002F7900, p);
    else func_0014E4C8(&D_002DDF40, 1, 6, 0, 0, 0);
}
