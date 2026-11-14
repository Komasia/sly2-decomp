#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; char pad2[0x1020]; int f1030; };
struct S { struct O *po; };
int FAsegaRetracted(int) asm("FAsegaRetracted__FP5ASEGA");
// name: SafeHouse port (UpdateSlyDodgeTransitions)
void UpdateSlyDodgeTransitions__FP3SLY(struct S *p) {
    if (FAsegaRetracted(p->po->f1030)) {
        struct O *po = p->po; VTENT *vt = po->vt;
        ((void (*)(void *, int))vt[88].pfn)(VT_THIS(po, &vt[88]), 0);
    }
}
