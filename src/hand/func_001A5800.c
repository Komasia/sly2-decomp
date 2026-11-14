#include "vtbl.h"
typedef unsigned long ulong;
struct O { char pad[0xC]; VTENT *vt; char pad2[0x18]; ulong fl; };
void OnLoAdd__FP2LO(struct O *p)
{
    VTENT *e;
    p->fl |= (ulong)1 << 60;
    e = &p->vt[4];
    ((void (*)(void *, int, void *))e->pfn)(VT_THIS(p, e), 0, p);
}
