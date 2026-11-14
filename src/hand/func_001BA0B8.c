#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct S { char pad[0x1050]; struct O *po; };
void ResetGuard__FP2LO(struct S *p);
void func_001BA0B8(struct S *p)
{
    struct O *po;
    ResetGuard__FP2LO(p);
    po = p->po;
    if (po) {
        VTENT *e = &po->vt[9];
        ((void (*)(void *))e->pfn)(VT_THIS(po, e));
    }
}
