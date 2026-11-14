#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { int n0; int c; struct O *ap[1]; };
// name: SafeHouse port (UpdateJobs)
void UpdateJobs__FP5ACTOR(struct S *p)
{
    int i;
    for (i = p->c; --i >= 0;) {
        struct O *po = p->ap[i];
        ((void (*)(void *))po->vt[10].pfn)(VT_THIS(po, &po->vt[10]));
    }
}
