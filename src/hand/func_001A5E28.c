#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x20]; float x30; };
extern float g_clock;
// name: SafeHouse port (UpdateLo)
void UpdateLo__FP2LO(struct O *p)
{
    if (p->x30 <= g_clock) {
        VTENT *e = &p->vt[3];
        ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(p, e), 1, 1, 0, 0, 0);
    }
}
