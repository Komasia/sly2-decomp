/* v2 (Claude agent, 2026-10-23): aligned 9 (was 11): dead scalar copy stored to a volatile qword local (func_001B50B0 trick). Target delays those stores. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef struct { float m[4][4]; } M4;
static inline qword Mulx(qword a, int g)
{
    volatile qword u;
    qword s, r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s));
    u = s;
    return r;
}
M4 *func_0011C210(M4 *pm, qword pos, M3 *pmat, int *pg)
{
    *(qword *)pm->m[0] = Mulx(pmat->r[0], pg[0]);
    *(qword *)pm->m[1] = Mulx(pmat->r[1], pg[1]);
    *(qword *)pm->m[2] = Mulx(pmat->r[2], pg[2]);
    *(qword *)pm->m[3] = pos;
    pm->m[0][3] = pm->m[1][3] = pm->m[2][3] = 0.0f;
    pm->m[3][3] = 1.0f;
    return pm;
}
