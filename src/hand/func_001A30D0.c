/* HideSubtitleBox (0x1A30D0): hides the cut scenes' subtitle box (its vtable slot 50). SafeHouse soundglue.cpp. */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; };
struct DIALOGSUB { struct LO *ploBox; };
#define VT_HIDE 50
// name: SafeHouse port (HideSubtitleBox)
void HideSubtitleBox__FP9DIALOGSUB(struct DIALOGSUB *pds) { struct LO *plo = pds->ploBox; if (plo) { VTENT *e = &plo->vt[VT_HIDE]; ((void (*)(void *))e->pfn)(VT_THIS(plo, e)); } }
