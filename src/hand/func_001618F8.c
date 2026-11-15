/* StartHudTimer: show the HUD timer (the screen object at SW +0x3BC4, vt slot 49) counting down to now + dt (SW
 * +0x476C, SafeHouse screenrt.h). */
#include "vtbl.h"
struct SCREENOBJ { char pad[0xC]; VTENT *vt; char pad2[0x8C - 0x10]; int f8c; };
struct SW { char pad[0x3BC4]; struct SCREENOBJ *pscrobjTimer; char pad2[0x476C - 0x3BC8]; float tTimerEnd; };
#include "clock.h"
// name: SafeHouse port (StartHudTimer)
void StartHudTimer__FPvf(struct SW *psw, float dt)
{
    struct SCREENOBJ *pscrobj = psw->pscrobjTimer;
    if (pscrobj) {
        VTENT *pvte;
        pscrobj->f8c = 0;
        pvte = &pscrobj->vt[49];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pscrobj, pvte), -1);
    }
    psw->tTimerEnd = g_clock.t + dt;
}
