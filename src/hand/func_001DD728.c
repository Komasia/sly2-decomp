#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct S { int a, b, c; VTENT *vt; char pad[0x14]; struct O *po; };
void func_001DD728(struct S *p) {
    if (p->po) {
        {
            VTENT *e = &p->vt[11];
            ((void (*)(void *))e->pfn)(VT_THIS(p, e));
        }
        {
            struct O *po = p->po;
            VTENT *e = &po->vt[50];
            ((void (*)(void *))e->pfn)(VT_THIS(po, e));
        }
    }
}
