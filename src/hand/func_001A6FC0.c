/* ConvertVec (0x1A6FC0): converts a direction from ploFrom's frame (null: the world) to ploTo's (null: the world),
 * through their rotation matrices (MatJtLo) and the inverse of the second. SafeHouse so.cpp. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
M3 *MatJtLo__FP2LO(void *p);
void InverseMatrix3__FP7MATRIX3(M3 *pm, M3 *pn);
// name: SafeHouse port (ConvertVec)
qword ConvertVec__FP2LOT0G9VU_VECTOR(void *ploFrom, void *ploTo, qword v)
{
    if (ploFrom) {
        M3 *pm = MatJtLo__FP2LO(ploFrom);
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "j"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]));
    }
    if (ploTo) {
        M3 m;
        InverseMatrix3__FP7MATRIX3(&m, MatJtLo__FP2LO(ploTo));
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    }
    return v;
}
