struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
struct B { int pad[3]; int nC; int pad10; struct O *po; };
struct A { int pad[4]; struct B *pb; };
extern char g_cm[];
void Deactivate__5CPLCYP2LOPv(struct A *a, int n, struct B *b);
void func_0014D8C0(void *p);
// name: SafeHouse port (CPTIMED::Deactivate)
void Deactivate__7CPTIMEDP2LOPv(struct A *a, int n, struct B *b)
{
    struct O *o;
    struct VTE *e;
    Deactivate__5CPLCYP2LOPv(a, n, b);
    if (b->nC)
        func_0014D8C0(g_cm);
    o = a->pb->po;
    e = &o->vt[2];
    e->pfn((char *)o + e->d);
    a->pb = 0;
}
