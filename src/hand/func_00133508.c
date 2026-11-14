#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
struct N { struct O *po; int f4; struct N *pnext; };
struct S { int f0; int f4; struct N *pfirst; VTENT *vt; };
void func_00133508(struct S *p, int a, int b) {
    struct N *pn;
    ((void (*)(void *, int, int))p->vt[5].pfn)(VT_THIS(p, &p->vt[5]), a, b);
    for (pn = p->pfirst; pn; ) {
        struct O *po = pn->po;
        pn = pn->pnext;
        ((void (*)(void *, int, int))po->vt[5].pfn)(VT_THIS(po, &po->vt[5]), a, b);
    }
}
