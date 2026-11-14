#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
struct O { int x0, x4, x8; VTENT *vt; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *out, void *in);
void MulMatrix4__FP7MATRIX4T0Pv(M4 *out, void *a, M4 *b);
// name: SafeHouse port (AppendAloExtraDraws)
void AppendAloExtraDraws__FP5SCENEP3ALOff(struct O *o, void *m, float a, float b)
{
    M4 t;
    M4 r;
    M4 inv;
    M4 *pr = &r;
    M4 *pinv = &inv;
    VTENT *e = &o->vt[0xF8 / 8];
    InverseAffineMatrix4__FP7MATRIX4(pinv, ((void *(*)(void *))e->pfn)(VT_THIS(o, e)));
    MulMatrix4__FP7MATRIX4T0Pv(pr, m, pinv);
    t = r;
    e = &o->vt[0xA0 / 8];
    ((void (*)(void *, M4 *, int, float, float))e->pfn)(VT_THIS(o, e), &t, 0, a, b);
}
