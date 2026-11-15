/* The object's splice event 0x1A (vt slot 3, no arguments). */
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; };
void func_00141E30(struct LO *plo)
{
    VTENT *e = &plo->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(plo, e), 0x1A, 0, 0, 0, 0);
}
