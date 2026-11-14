#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct B { int a; struct O *po; };
// name: SafeHouse port (NotifyWaterObject)
void NotifyWaterObject__FP3ALOP5WNODE(void *p, struct B *b)
{
    struct O *po = b->po;
    ((void (*)(void *, void *))po->vt[72].pfn)(VT_THIS(po, &po->vt[72]), p);
}
