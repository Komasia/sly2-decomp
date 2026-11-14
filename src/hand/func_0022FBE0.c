#include "vtbl.h"
struct O { int a[3]; VTENT *vt; char pad[0x14]; struct O *next; };
struct S { char pad[0x64]; struct O *first; int a[2]; struct O *end; };
void UpdateAloXfWorlds__FP3ALO(struct S *p);
// name: SafeHouse port (UpdateAloXfWorldsHierarchy)
void UpdateAloXfWorldsHierarchy__FP3ALO(struct S *p)
{
    struct O *o;
    UpdateAloXfWorlds__FP3ALO(p);
    for (o = p->first; o != p->end; o = o->next)
        ((void (*)(void *))o->vt[18].pfn)(VT_THIS(o, &o->vt[18]));
}
