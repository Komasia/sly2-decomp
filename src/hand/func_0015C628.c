#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
void ExplodeExplsExplso__FP5EXPLSP6EXPLSO(struct O *o, int x)
{
    VTENT *e = &o->vt[52];
    ((void (*)())e->pfn)(VT_THIS(o, e), x);
}
