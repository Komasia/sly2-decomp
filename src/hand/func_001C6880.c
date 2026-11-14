struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct O { int a[3]; struct VTE *vt; char pad[0x140]; int n150; char pad2[0xE4]; float g238; };
#include "clock.h"
void UpdatePickupBase__FP2LO(struct O *p);
void func_001C6880(struct O *p)
{
    UpdatePickupBase__FP2LO(p);
    if (!p->n150) {
        p->g238 -= g_clock.dt;
        if (p->g238 <= 0.0f) { struct VTE *e = &p->vt[76]; e->pfn((char *)p + e->d, 5); }
    }
}
