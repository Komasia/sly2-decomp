#include "vtbl.h"
struct S { int a[3]; VTENT *vt; char pad[0x158]; char y[4]; };
void OnSoRemove__FP2SO(struct S *p);
void ClearSmaHandle__FPP3SMA(void *d);
// name: SafeHouse port (OnCarryRemove)
void OnCarryRemove__FP2LO(struct S *p)
{
    OnSoRemove__FP2SO(p);
    ((void (*)(void *, int))p->vt[76].pfn)(VT_THIS(p, &p->vt[76]), -1);
    ClearSmaHandle__FPP3SMA(p->y);
}
