#include "vtbl.h"
#include "clock.h"
struct O { int a[3]; VTENT *vt; int pad[6]; unsigned long fl; int pad2[14]; float t68; };
// name: SafeHouse port (StartFadeLo)
void StartFadeLo__FP2LO(struct O *o)
{
    if (!((int)(o->fl >> 60) & 1)) {
        VTENT *e = &o->vt[8];
        o->t68 = g_clock.t;
        ((void (*)())e->pfn)(VT_THIS(o, e));
    }
}
