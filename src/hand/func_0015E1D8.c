/* StartFadeLo: start a screen fade (cid 0x74): unless it is already in the world (LO flag bit 60), note its start
 * time and add it (vtable entry 8, AddLo). */
#include "vtbl.h"
#include "clock.h"
struct FADE { int a[3]; VTENT *vt; int pad[6]; unsigned long grf; int pad2[14]; float tStart; };
// name: SafeHouse port (StartFadeLo)
void StartFadeLo__FP2LO(struct FADE *pfade)
{
    if (!((int)(pfade->grf >> 60) & 1)) {
        VTENT *pvte = &pfade->vt[8];
        pfade->tStart = g_clock.t;
        ((void (*)())pvte->pfn)(VT_THIS(pfade, pvte));
    }
}
