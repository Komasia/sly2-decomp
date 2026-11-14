#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { char pad[0x44]; struct O *p44; int n48; };
// name: SafeHouse port (JOBINVESTIGATE::SetNoise)
void SetNoise__14JOBINVESTIGATEP5NOISE(struct S *p, struct O *o) {
    if (o == p->p44) return;
    if (p->p44) { VTENT *e = &p->p44->vt[2]; ((void (*)(void *))e->pfn)(VT_THIS(p->p44, e)); }
    p->p44 = o;
    if (o) { VTENT *e = &o->vt[1]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
    p->n48 = 1;
}
