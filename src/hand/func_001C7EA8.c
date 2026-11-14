#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
void func_001CB5D0(struct O *p);
// name: SafeHouse port (DetachCluePlacement)
void DetachCluePlacement__FP2LO(struct O *p)
{
    func_001CB5D0(p);
    { VTENT *e = &p->vt[76]; ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), -1); }
}
