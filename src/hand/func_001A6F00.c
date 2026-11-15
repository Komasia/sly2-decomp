/* ConvertPos (0x1A6F00): converts a position from ploFrom's frame (null: the world) to ploTo's (null: the world),
 * through their world matrices (vtable entry 31) and the inverse of the second. SafeHouse so.cpp. */
#include "so.h"
typedef struct { qword r[4]; } M4;
struct LO;
void InverseAffineMatrix4__FP7MATRIX4(M4 *pm, M4 *pn);
// name: SafeHouse port (ConvertPos)
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct LO *ploFrom, struct LO *ploTo, qword v)
{
    if (ploFrom) {
        M4 *pm = ((M4 * (*)(struct LO *))ploFrom->pvt[31].pfn)((struct LO *)VT_THIS(ploFrom, &ploFrom->pvt[31]));
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
                : "=j"(v) : "j"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]));
    }
    if (ploTo) {
        M4 m;
        InverseAffineMatrix4__FP7MATRIX4(&m, ((M4 * (*)(struct LO *))ploTo->pvt[31].pfn)((struct LO *)VT_THIS(ploTo, &ploTo->pvt[31])));
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddaz.xyz $ACC, %4, %1z\n\tvmaddw.xyz %0, %5, $vf0w"
                : "=j"(v) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]));
    }
    return v;
}
