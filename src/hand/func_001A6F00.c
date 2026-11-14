#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
struct LO;
struct LO { int x0, x4, x8; VTENT *vt; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *pm, M4 *pn);
// name: SafeHouse port (ConvertPos)
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct LO *a, struct LO *b, qword v)
{
    if (a) {
        M4 *pm = ((M4 * (*)(struct LO *))a->vt[31].pfn)((struct LO *)VT_THIS(a, &a->vt[31]));
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
                : "=j"(v) : "j"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]));
    }
    if (b) {
        M4 m;
        InverseAffineMatrix4__FP7MATRIX4(&m, ((M4 * (*)(struct LO *))b->vt[31].pfn)((struct LO *)VT_THIS(b, &b->vt[31])));
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
                : "=j"(v) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]));
    }
    return v;
}
