#include "vtbl.h"
struct O { int a[3]; VTENT *vt; char pad[0x140]; int n150; char pad2[0xE4]; float g238; };
#include "clock.h"
void UpdatePickupBase__FP2LO(struct O *p);
void func_001C7778(struct O *p)
{
    UpdatePickupBase__FP2LO(p);
    if (!p->n150) {
        p->g238 -= g_clock.dt;
        if (p->g238 <= 0.0f) { VTENT *e = &p->vt[76]; ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), 5); }
    }
}
