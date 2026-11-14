#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct B { int pad[3]; int nC; int pad10; struct O *po; };
struct A { int pad[4]; struct B *pb; };
extern char g_cm[];
void Deactivate__5CPLCYP2LOPv(struct A *a, int n, struct B *b);
void CutCm(void *p) asm("CutCm__FP2CM");
// name: SafeHouse port (CPTIMED::Deactivate)
void Deactivate__7CPTIMEDP2LOPv(struct A *a, int n, struct B *b)
{
    struct O *o;
    VTENT *e;
    Deactivate__5CPLCYP2LOPv(a, n, b);
    if (b->nC)
        CutCm(g_cm);
    o = a->pb->po;
    e = &o->vt[2];
    ((void (*)())e->pfn)(VT_THIS(o, e));
    a->pb = 0;
}
