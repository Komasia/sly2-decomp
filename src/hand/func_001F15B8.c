#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct S { struct O *po; };
void RetractSma__FP3SMA(struct O *);
// name: SafeHouse port (ClearSmaHandle)
void ClearSmaHandle__FPP3SMA(struct S *p)
{
    if (p->po) {
        RetractSma__FP3SMA(p->po);
        { struct O *po = p->po; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }
        p->po = 0;
    }
}
