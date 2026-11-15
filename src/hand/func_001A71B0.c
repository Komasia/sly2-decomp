/* func_001A71B0 (0x1A71B0): converts a full transform matrix from ploFrom's frame (null: the world) to ploTo's (null:
 * the world): times ploFrom's world matrix (vtable entry 31), then the inverse of ploTo's. See ConvertPos. */
#include "vtbl.h"
#define VT_MAT_WORLD (0xF8 / 8)  /* entry 31 */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
struct O { int x0, x4, x8; VTENT *vt; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *out, void *in);
void MulMatrix4__FP7MATRIX4T0Pv(M4 *out, void *a, M4 *b);
M4 func_001A71B0(struct O *ploFrom, struct O *ploTo, M4 *pmat)
{
    M4 t;
    M4 r;
    M4 inv;
    VTENT *e;
    if (ploFrom) {
        e = &ploFrom->vt[VT_MAT_WORLD];
        MulMatrix4__FP7MATRIX4T0Pv(&r, ((void * (*)(void *))e->pfn)(VT_THIS(ploFrom, e)), pmat);
        t = r;
    } else {
        t = *pmat;
    }
    if (ploTo) {
        M4 *pinv = &inv;
        M4 *pr = &r;
        e = &ploTo->vt[VT_MAT_WORLD];
        InverseAffineMatrix4__FP7MATRIX4(pinv, ((void * (*)(void *))e->pfn)(VT_THIS(ploTo, e)));
        MulMatrix4__FP7MATRIX4T0Pv(pr, pinv, &t);
        t = r;
    }
    return t;
}
