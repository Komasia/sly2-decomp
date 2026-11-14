#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
void func_001CB518(struct O *p);
// name: SafeHouse port (ResetCluePlacement)
void ResetCluePlacement__FP2LO(struct O *p)
{
    func_001CB518(p);
    { VTENT *e = &p->vt[76]; ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), 0); }
}
