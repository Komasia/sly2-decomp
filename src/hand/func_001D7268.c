/* class: the safe house, class 0x46 (vt slot 15, its post-load): the base post-load, then disable it (vt slot 79,
 * func_001D7418 with 0: not shown). */
#include "vtbl.h"
struct SAFEHOUSE { int pad0[3]; VTENT *vt; };
void func_001F36A8(struct SAFEHOUSE *psh);

void func_001D7268(struct SAFEHOUSE *psh)
{
    VTENT *pvtent;
    func_001F36A8(psh);
    pvtent = &psh->vt[79];
    ((void (*)(void *, int))pvtent->pfn)(VT_THIS(psh, pvtent), 0);
}
