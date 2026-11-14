#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; char pad2[0x14]; struct O *x24; char pad3[0x18]; int x40; };
void func_001ACB58(struct O *p, int a)
{
    p->x40 = a;
    if (p->x24) {
        { VTENT *e = &p->vt[10]; ((void (*)())e->pfn)(VT_THIS(p, e)); }
        { struct O *o = p->x24; VTENT *e = &o->vt[49]; ((void (*)())e->pfn)(VT_THIS(o, e), -1); }
    }
}
