/* func_001ACBB8 (0x1ACBB8): the memory card prompt hides its message (+0x40 -1): with its screen object (+0x24) the
 * prompt's vtable entry 11 (hide) and the screen object's entry 50 (hide). */
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x14]; struct O *ploScreen; char pad3[0x18]; int msg; };
#define VT_WIDGET_HIDE 11
#define VT_SCREEN_HIDE 50
void func_001ACBB8(struct O *pprompt)
{
    pprompt->msg = -1;
    if (pprompt->ploScreen) {
        { VTENT *e = &pprompt->vt[VT_WIDGET_HIDE]; ((void (*)())e->pfn)(VT_THIS(pprompt, e)); }
        { struct O *ploScreen = pprompt->ploScreen; VTENT *e = &ploScreen->vt[VT_SCREEN_HIDE]; ((void (*)())e->pfn)(VT_THIS(ploScreen, e)); }
    }
}
