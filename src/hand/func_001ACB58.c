/* func_001ACB58 (0x1ACB58): the memory card prompt shows a message (+0x40): with its screen object (+0x24) the prompt's
 * vtable entry 10 (show) and the screen object's entry 49 (show, -1). */
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x14]; struct O *ploScreen; char pad3[0x18]; int msg; };
#define VT_WIDGET_SHOW 10
#define VT_SCREEN_SHOW 49
void func_001ACB58(struct O *pprompt, int msg)
{
    pprompt->msg = msg;
    if (pprompt->ploScreen) {
        { VTENT *e = &pprompt->vt[VT_WIDGET_SHOW]; ((void (*)())e->pfn)(VT_THIS(pprompt, e)); }
        { struct O *ploScreen = pprompt->ploScreen; VTENT *e = &ploScreen->vt[VT_SCREEN_SHOW]; ((void (*)())e->pfn)(VT_THIS(ploScreen, e), -1); }
    }
}
