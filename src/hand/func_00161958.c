#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x3BC4]; struct O *po; char pad2[0x476C - 0x3BC8]; int n; };
// name: SafeHouse port (StopHudTimer)
void StopHudTimer__FPv(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        VTENT *e = &po->vt[50];
        ((void (*)(void *))e->pfn)(VT_THIS(po, e));
    }
    p->n = 0;
}
