#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
extern char g_sw[];
struct O *PloPlayerPo__FP2SW(void *g);
// name: SafeHouse port (TriggerWarp)
void TriggerWarp__FP4WARP(struct O *p)
{
    struct O *o = PloPlayerPo__FP2SW(g_sw);
    if (o) {
        ((void (*)())o->vt[38].pfn)(VT_THIS(o, &o->vt[38]), p);
        ((void (*)())p->vt[3].pfn)(VT_THIS(p, &p->vt[3]), 5, 0, 0, 0, 0);
    }
}
