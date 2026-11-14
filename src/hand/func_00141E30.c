#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
void func_00141E30(struct O *p)
{
    VTENT *e = &p->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(p, e), 0x1A, 0, 0, 0, 0);
}
