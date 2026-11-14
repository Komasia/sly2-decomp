#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
struct O { int x0, x4, x8; VTENT *vt; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *out, void *in);
void MulMatrix4__FP7MATRIX4T0Pv(M4 *out, void *a, M4 *b);
M4 func_001A71B0(struct O *o1, struct O *o2, M4 *m)
{
    M4 t;
    M4 r;
    M4 inv;
    VTENT *e;
    if (o1) {
        e = &o1->vt[0xF8 / 8];
        MulMatrix4__FP7MATRIX4T0Pv(&r, ((void * (*)(void *))e->pfn)(VT_THIS(o1, e)), m);
        t = r;
    } else {
        t = *m;
    }
    if (o2) {
        M4 *pinv = &inv;
        M4 *pr = &r;
        e = &o2->vt[0xF8 / 8];
        InverseAffineMatrix4__FP7MATRIX4(pinv, ((void * (*)(void *))e->pfn)(VT_THIS(o2, e)));
        MulMatrix4__FP7MATRIX4T0Pv(pr, pinv, &t);
        t = r;
    }
    return t;
}
