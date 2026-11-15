/* StopHudTimer: hide the HUD timer (vt slot 50) and clear its end time. */
#include "vtbl.h"
struct SCREENOBJ { char pad[0xC]; VTENT *vt; };
struct SW { char pad[0x3BC4]; struct SCREENOBJ *pscrobjTimer; char pad2[0x476C - 0x3BC8]; int tTimerEnd; };
// name: SafeHouse port (StopHudTimer)
void StopHudTimer__FPv(struct SW *psw)
{
    struct SCREENOBJ *pscrobj = psw->pscrobjTimer;
    if (pscrobj) {
        VTENT *pvte = &pscrobj->vt[50];
        ((void (*)(void *))pvte->pfn)(VT_THIS(pscrobj, pvte));
    }
    psw->tTimerEnd = 0;
}
