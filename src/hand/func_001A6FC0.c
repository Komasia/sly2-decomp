typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
M3 *MatJtLo__FP2LO(void *p);
void func_0011B340(M3 *pm, M3 *pn);
// name: SafeHouse port (ConvertVec)
qword ConvertVec__FP2LOT0G9VU_VECTOR(void *a, void *b, qword v)
{
    if (a) {
        M3 *pm = MatJtLo__FP2LO(a);
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "j"(v), "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]));
    }
    if (b) {
        M3 m;
        func_0011B340(&m, MatJtLo__FP2LO(b));
        __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                : "=j"(v) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    }
    return v;
}
