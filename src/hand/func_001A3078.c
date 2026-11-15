/* ShowSubtitleBox (0x1A3078): shows the cut scenes' subtitle box (DIALOGSUB +0x0, the screen object 0x373): resets the
 * dialog's subtitle state (0x227788 on D_004435F0), then the box's vtable slot 49 (show) with -1. SafeHouse soundglue.cpp. */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; };
struct DIALOGSUB { struct LO *ploBox; };
#define VT_SHOW 49
extern char g_dialogsub[] __asm__("D_004435F0");  /* the dialog's subtitle state {id, rgba, grf} */
void func_00227788(void *pdialogsub);
// name: SafeHouse port (ShowSubtitleBox)
void ShowSubtitleBox__FP9DIALOGSUB(struct DIALOGSUB *pds)
{
    if (pds->ploBox) {
        struct LO *plo;
        VTENT *e;
        func_00227788(g_dialogsub);
        plo = pds->ploBox;
        e = &plo->vt[VT_SHOW];
        ((void (*)(void *, int))e->pfn)(VT_THIS(plo, e), -1);
    }
}
