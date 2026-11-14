#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct S { char pad[0x18C4]; struct O *o; };
float atan2f(float, float);
// name: SafeHouse port (RadHangFrame)
void RadHangFrame__FP3SLYPf(struct S *p, float *pg) {
    float *a, *b;
    { struct O *o = p->o; VTENT *e = &o->vt[31]; a = ((float * (*)(void *))e->pfn)(VT_THIS(o, e)); }
    { struct O *o = p->o; VTENT *e = &o->vt[31]; b = ((float * (*)(void *))e->pfn)(VT_THIS(o, e)); }
    *pg = atan2f(a[1], b[0]);
}
