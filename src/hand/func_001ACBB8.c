#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x14]; struct O *x24; char pad3[0x18]; int x40; };
void func_001ACBB8(struct O *p)
{
    p->x40 = -1;
    if (p->x24) {
        { VTENT *e = &p->vt[11]; ((void (*)())e->pfn)(VT_THIS(p, e)); }
        { struct O *o = p->x24; VTENT *e = &o->vt[50]; ((void (*)())e->pfn)(VT_THIS(o, e)); }
    }
}
