/* 7 diffs: matRot row loads r0/r1 order (regs right), matT/mat copy stores not interleaved per row, VU_FLOAT temp slot 0x40 vs 0x10. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { qword q; float g; } UF;
struct SMP;
M3 func_0011BC00(M3 *pa, M3 *pb);
void func_0011BCF8(M3 *pmat, float *prad, qword *pvec);
float func_0011D018(float g, float gGoal, float dt, struct SMP *psmp, float *pdv);
M3 func_0011B500(float rad, qword axis);
static inline qword MulRow(qword a0, qword a1, qword a2, qword r)
{
    qword m;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m) : "j"(a0), "j"(a1), "j"(a2), "j"(r));
    return m;
}
static inline M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    qword a1 = pa->r[1], a0 = pa->r[0], a2 = pa->r[2];
    m.r[0] = MulRow(a0, a1, a2, pb->r[0]);
    m.r[1] = MulRow(a0, a1, a2, pb->r[1]);
    m.r[2] = MulRow(a0, a1, a2, pb->r[2]);
    return m;
}
void SmoothMatrix(M3 *pmatPrev, M3 *pmatGoal, struct SMP *psmp, float dt, M3 *pmatNext, qword *pw)
{
    UF normal;
    float rad, dv, radNew;
    {
    M3 mat;
    mat = func_0011BC00(pmatPrev, pmatGoal);
    func_0011BCF8(&mat, &rad, &normal.q);
    radNew = func_0011D018(0.0f, rad, dt, psmp, &dv);
    if (pmatNext) {
        if (radNew == rad) {
            *pmatNext = *pmatGoal;
        } else {
            M3 matRot = func_0011B500(radNew, normal.q);
            mat = MulM3(&matRot, pmatPrev);
            *pmatNext = mat;
        }
    }
    }
    if (pw) {
        UF u;
        qword r;
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(*(int *)&dv));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(normal.q), "j"(u.q));
        *pw = r;
    }
}
