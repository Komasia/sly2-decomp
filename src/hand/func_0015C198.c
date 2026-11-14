#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct O { int a[3]; VTENT *vt; };
struct P { int a; int b; float f; float g; qword q; qword r; qword s; };
void ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff(struct O *o, int a, int b, float f, float g, qword q, qword r)
{
    struct P p;
    VTENT *e;
    p.a = a;
    p.b = b;
    p.f = f;
    p.g = g;
    p.q = q;
    p.r = r;
    e = &o->vt[51];
    ((void (*)())e->pfn)(VT_THIS(o, e), &p);
}
