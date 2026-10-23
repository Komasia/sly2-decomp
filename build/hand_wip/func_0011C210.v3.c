/* v3 (Claude agent, lane A26, 2026-10-23): aligned 6 (v2: 9). The dead scale stores are sqc2 "=m" asms placed one row LATE, each with an allocation-only "j" operand on the next row's scale, so s0/s1/s2 get vf2/vf3/vf2 like the target. Left: row-0 qmtc2/lqc2 order, pg[2] in v1 (target a3), s1 store too early. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef struct { float m[4][4]; } M4;
static inline qword Q(int g)
{
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    return s;
}
static inline qword Mul(qword a, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s));
    return r;
}
M4 *func_0011C210(M4 *pm, qword pos, M3 *pmat, int *pg)
{
    union { qword q; float f[4]; } u;
    qword s0, s1, s2;
    s0 = Q(pg[0]);
    *(qword *)pm->m[0] = Mul(pmat->r[0], s0);
    s1 = Q(pg[1]);
    __asm__("sqc2 %1, %0" : "=m"(u.q) : "j"(s0), "j"(s1)); /* "j"(s1): allocation-only operand */
    *(qword *)pm->m[1] = Mul(pmat->r[1], s1);
    s2 = Q(pg[2]);
    __asm__("sqc2 %1, %0" : "=m"(u.q) : "j"(s1), "j"(s2)); /* "j"(s2): allocation-only operand */
    *(qword *)pm->m[2] = Mul(pmat->r[2], s2);
    __asm__("sqc2 %1, %0" : "=m"(u.q) : "j"(s2));
    *(qword *)pm->m[3] = pos;
    pm->m[0][3] = pm->m[1][3] = pm->m[2][3] = 0.0f;
    pm->m[3][3] = 1.0f;
    return pm;
}
