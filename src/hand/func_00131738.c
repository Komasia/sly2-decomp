#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; int pad2[2]; struct O *f18; };
struct G { struct O *po; };
void func_00133508(struct O *, int, int);
void func_00131738(struct O *p, int a, int b) {
    struct G volatile g;
    g.po = p;
    ((void (*)(void *))p->vt[1].pfn)(VT_THIS(p, &p->vt[1]));
    if (p->f18) ((void (*)(void *, int, int))p->f18->vt[5].pfn)(VT_THIS(p->f18, &p->f18->vt[5]), a, b);
    func_00133508(p, a, b);
    { struct O *po = g.po; ((void (*)(void *))po->vt[2].pfn)(VT_THIS(po, &po->vt[2])); }
}
