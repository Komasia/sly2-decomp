#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; int pad2[2]; int f18; };
struct R { int f0; int f4; };
struct O *PloNew__F3CIDP2SW3OIDi(int, int, int, int);
// name: SafeHouse port (PloCloneLo)
struct O *PloCloneLo__FP2LOi(struct O *po, int a) {
    struct R *pr;
    struct O *pn;
    if (!po) return 0;
    pr = (struct R *)((void *(*)(void *))po->vt[6].pfn)(VT_THIS(po, &po->vt[6]));
    pn = PloNew__F3CIDP2SW3OIDi(pr->f4, a, po->f18, -1);
    ((void (*)(void *, struct O *))pn->vt[40].pfn)(VT_THIS(pn, &pn->vt[40]), po);
    return pn;
}
