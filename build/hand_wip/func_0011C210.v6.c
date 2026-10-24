/* v6 (Claude agent, lane A28, 2026-10-24): aligned 2 (v5: 3). v5 plus an ordering-only "m"(u.q) input on the s0 qmtc2 (Q0): the later sqc2 stores to u become anti-dependents, so qmtc2 s0 beats lqc2 row 0 (11 deps each, lower LUID wins) at sched2 t=2. Left: pg[2] in v1 (target a3); a dead "$3" clobber on Q(pg[2]) gives t0. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef struct { float m[4][4]; } M4;
static inline qword Q(int g)
{
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    return s;
}
static inline qword Q0(int g, qword *pu)
{
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g), "m"(*pu)); /* "m": ordering-only operand */
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
    s0 = Q0(pg[0], &u.q);
    *(qword *)pm->m[0] = Mul(pmat->r[0], s0);
    s1 = Q(pg[1]);
    __asm__("sqc2 %1, %0" : "=m"(u.q) : "j"(s0), "j"(s1)); /* "j"(s1): allocation-only operand */
    *(qword *)pm->m[1] = Mul(pmat->r[1], s1);
    s2 = Q(pg[2]);
    *(qword *)pm->m[2] = Mul(pmat->r[2], s2);
    *(qword *)pm->m[3] = pos;
    __asm__("sqc2 %1, %0" : "=m"(u.q) : "j"(s1), "j"(s2)); /* "j"(s2): allocation-only operand */
    pm->m[0][3] = pm->m[1][3] = pm->m[2][3] = 0.0f;
    pm->m[3][3] = 1.0f;
    __asm__("sqc2 %1, %0" : "=m"(u.q) : "j"(s2), "m"(pm->m[0][3])); /* "m": ordering-only operand */
    return pm;
}
