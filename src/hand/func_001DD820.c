/* ShowTitle (SafeHouse port): show the title HUD widget D_003DA530 - its Show (vtable entry 10), its screen object
 * shown (entry 49, -1), and the vibration option leaves its boot value (RumbleUnknown1). */
#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct HUDWIDGET {
    /* 0x00 */ int a, b, c;
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ char pad10[0x14];
    /* 0x24 */ struct O *pscreen;
};
void RumbleUnknown1(void) asm("RumbleUnknown1__Fv");
// name: SafeHouse port (ShowTitle)
void ShowTitle__FPv(struct HUDWIDGET *pwidget) {
    if (pwidget->pscreen) {
        {
            VTENT *pvtent = &pwidget->vt[10];
            ((void (*)(void *))pvtent->pfn)(VT_THIS(pwidget, pvtent));
        }
        {
            struct O *pscreen = pwidget->pscreen;
            VTENT *pvtent = &pscreen->vt[49];
            ((void (*)(void *, int))pvtent->pfn)(VT_THIS(pscreen, pvtent), -1);
        }
        RumbleUnknown1();
    }
}
