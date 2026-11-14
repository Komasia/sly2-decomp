
#include "vtbl.h"
struct OW { char pad[0x26C]; int x; };
struct O { char pad[0xC]; VTENT *vt; struct OW *pow; };
struct S { struct O *po; };
void func_001EEED0(int *p);
// name: SafeHouse port (EndChildJob)
void EndChildJob__FPP5AIJOB(struct S *p)
{
    struct O *po = p->po;
    if (po) {
        int *px = &po->pow->x;
        ((void (*)(void *))po->vt[9].pfn)(VT_THIS(po, &po->vt[9]));
        func_001EEED0(px);
        p->po = 0;
    }
}
