struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
struct B { int pad[5]; struct O *po; };
struct A { int pad[4]; struct B *pb; };
void Activate__5CPLCYP2LOPv(struct A *a, int n, struct B *b);
// name: SafeHouse port (CPTIMED::Activate)
void Activate__7CPTIMEDP2LOPv(struct A *a, int n, struct B *b)
{
    struct O *o;
    struct VTE *e;
    Activate__5CPLCYP2LOPv(a, n, b);
    a->pb = b;
    o = b->po;
    e = &o->vt[1];
    e->pfn((char *)o + e->d);
}
