#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
struct S { int f0; int f4; int f8; };
void ReparentBooty__FP3ALOii(struct O *, int, int);
void func_0013F990(struct O *, int);
void func_0013FA30(struct S *p, int c, struct O **apo) {
    int i;
    for (i = 0; i < c; i++) {
        struct O *po = apo[i];
        ReparentBooty__FP3ALOii(po, 0, 0);
        func_0013F990(po, p->f4);
        if (p->f8 != -1) ((void (*)(void *, int, int))po->vt[25].pfn)(VT_THIS(po, &po->vt[25]), p->f8, 1);
    }
}
