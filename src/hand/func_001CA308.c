#include "vtbl.h"
struct O { int a[3]; VTENT *vt; char pad[0x14]; struct O *pNext; char pad2[0x3C]; struct O *pFirst; };
void SetIdProxy(struct O *p, void *a) asm("SetIdProxy__2LOii");
void func_001CA308(struct O *p, void *a)
{
    struct O *o;
    int unused[4];
    SetIdProxy(p, a);
    for (o = p->pFirst; o; o = o->pNext) { VTENT *e = &o->vt[25]; ((void (*)(void *, void *, int))e->pfn)(VT_THIS(o, e), a, 0); }
}
