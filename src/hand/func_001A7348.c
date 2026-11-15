/* func_001A7348 (0x1A7348): ConvertVec on matrices: a direction through pmatFrom (if given), then through an inverse
 * rotation when fInverse is set (InverseMatrix3 into a local). */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
void InverseMatrix3__FP7MATRIX3(M3 *pm);
qword func_001A7348(M3 *pm, int fInverse, qword v)
{
    if (pm) {
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "j"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]));
    }
    if (fInverse) {
        M3 m;
        InverseMatrix3__FP7MATRIX3(&m);
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    }
    return v;
}
