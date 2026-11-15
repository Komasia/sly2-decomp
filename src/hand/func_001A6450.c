/* func_001A6450 (0x1A6450): passes a call on to the LO's children: each child the LO's vt slot 28 lists gets its
 * vt slot 37 with the argument. */
#include "vtbl.h"
struct O { int x0, x4, x8; VTENT *vt; };
#define VT_CHILDREN (0xE0 / 8)  /* slot 28 */
#define VT_37 (0x128 / 8)
void func_001A6450(struct O *plo, void *pv)
{
    struct O **aploChild;
    int cploChild, i;
    VTENT *e = &plo->vt[VT_CHILDREN];
    cploChild = ((int (*)(void *, struct O ***))e->pfn)(VT_THIS(plo, e), &aploChild);
    for (i = 0; i < cploChild; i++) {
        struct O *ploChild = aploChild[i];
        VTENT *f = &ploChild->vt[VT_37];
        ((void (*)(void *, void *))f->pfn)(VT_THIS(ploChild, f), pv);
    }
}
