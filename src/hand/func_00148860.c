#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
void RunTriggerList__FP2LOi(void *p, int n);
// name: SafeHouse port (LeavePad)
void LeavePad__FP2LO(struct O **p)
{
    struct O *o = *p;
    VTENT *e = &o->vt[3];
    ((void (*)(void *, int, int, int, int, int))e->pfn)(VT_THIS(o, e), 6, 0, 0, 0, 0);
    RunTriggerList__FP2LOi(p, 1);
    {
        struct O *o2 = *p;
        VTENT *e2 = &o2->vt[4];
        ((void (*)(void *, int, void *))e2->pfn)(VT_THIS(o2, e2), 7, p);
    }
}
