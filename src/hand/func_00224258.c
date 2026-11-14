#include "vtbl.h"
struct O { int a[3]; VTENT *vt; char pad[0x14C]; int k; };
struct Q { char pad[0x18]; int k; };
void ReparentBooty__FP3ALOii(struct O *p, struct Q *q, int a);
// name: SafeHouse port (LandCarry)
void LandCarry__FP2LOT0(struct O *p, struct Q *q)
{
    int k = p->k;
    if (k == 0x1A || k == 0x29) ((void (*)())p->vt[76].pfn)(VT_THIS(p, &p->vt[76]), 3);
    else {
        ReparentBooty__FP3ALOii(p, q->k == 1 ? 0 : q, 3);
        ((void (*)())p->vt[76].pfn)(VT_THIS(p, &p->vt[76]), 2);
    }
}
