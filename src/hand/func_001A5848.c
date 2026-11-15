/* OnLoRemove (0x1A5848): LO vt slot 12: the LO is out of the world (bit 60 of +0x28 cleared), its references in the
 * heroes' safe-ground histories are removed (bit 59, func_001A00D0), then the BASIC notification (vtable slot 4) with 1
 * (removed). SafeHouse activate.cpp OnRemove. */
#include "vtbl.h"
struct VT { VTENT e[8]; };
struct S { int x0, x4, x8; struct VT *vt; char pad[0x18]; unsigned long x28; };
extern char g_sw[];
#define GRFLO_IN_WORLD 0x1000000000000000UL        /* bit 60 */
#define GRFLO_SAFEGROUND_REF 0x0800000000000000UL  /* bit 59 */
#define VT_NOTIFY 4
void func_001A00D0(void *g, struct S *s, int n);
void OnLoRemove__FP2LO(struct S *plo)
{
    plo->x28 &= ~GRFLO_IN_WORLD;
    if (plo->x28 & GRFLO_SAFEGROUND_REF)
        func_001A00D0(g_sw, plo, 0);
    ((void (*)(void *, int, void *))plo->vt->e[VT_NOTIFY].pfn)(VT_THIS(plo, &plo->vt->e[VT_NOTIFY]), 1, plo);
}
