#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct B { int pad[5]; struct O *po; };
struct A { int pad[4]; struct B *pb; };
void Activate__5CPLCYP2LOPv(struct A *a, int n, struct B *b);
// name: SafeHouse port (CPTIMED::Activate)
void Activate__7CPTIMEDP2LOPv(struct A *a, int n, struct B *b)
{
    struct O *o;
    VTENT *e;
    Activate__5CPLCYP2LOPv(a, n, b);
    a->pb = b;
    o = b->po;
    e = &o->vt[1];
    ((void (*)())e->pfn)(VT_THIS(o, e));
}
