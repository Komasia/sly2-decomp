typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
extern qword D_002A2DB0;
extern qword D_002A2DC0;
M3 func_0011BA08(qword a, qword b);
void *func_0023320C(void *pvDst, void *pvSrc, int cb);
static inline M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[0]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[1]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[2]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[2]));
    return m;
}
static inline qword MulRow(qword a0, qword a1, qword a2, qword b)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r) : "j"(a0), "j"(a1), "j"(a2), "j"(b));
    return r;
}
static inline M3 MulM3q(qword a0, qword a1, qword a2, M3 *pb)
{
    M3 m;
    m.r[0] = MulRow(a0, a1, a2, pb->r[0]);
    m.r[1] = MulRow(a0, a1, a2, pb->r[1]);
    m.r[2] = MulRow(a0, a1, a2, pb->r[2]);
    return m;
}
void func_0011B938(M3 *pm, M3 *pmA, M3 *pmB)
{
    M3 local;
    M3 t;
    M3 *p = pmA ? pmA : &local;
    qword a0, a1, a2;
    t = func_0011BA08(pm->r[2], D_002A2DC0);
    a0 = t.r[0]; p->r[0] = a0;
    a1 = t.r[1]; p->r[1] = a1;
    a2 = t.r[2]; p->r[2] = a2;
    if (pmB) {
        t = MulM3q(a0, a1, a2, pm);
        *pmB = t;
    }
}
