/* UpdateLo (0x1A5E28): the base update: once the update time (+0x30) is reached, the splice update event (vt slot 3
 * with (1, 1, 0, 0, 0)). */
#include "vtbl.h"
#define VT_SPLICE_EVENT 3
struct O { char pad[0xC]; VTENT *vt; char pad2[0x20]; float x30; };
extern float g_clock;
// name: SafeHouse port (UpdateLo)
void UpdateLo__FP2LO(struct O *plo)
{
    if (plo->x30 <= g_clock) {
        VTENT *e = &plo->vt[VT_SPLICE_EVENT];
        ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(plo, e), 1, 1, 0, 0, 0);
    }
}
