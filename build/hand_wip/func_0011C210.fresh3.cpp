typedef int qword __attribute__((mode(TI)));
struct VF { qword q; VF(int g) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(g)); } };
typedef struct { qword r[3]; } M3;
typedef struct { float m[4][4]; } M4;
static inline qword operator*(const qword &a, const VF &s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}
extern "C" M4 *func_0011C210(M4 *pm, qword pos, M3 *pmat, int *pg)
{
    *(qword *)pm->m[0] = pmat->r[0] * VF(pg[0]);
    *(qword *)pm->m[1] = pmat->r[1] * VF(pg[1]);
    *(qword *)pm->m[2] = pmat->r[2] * VF(pg[2]);
    *(qword *)pm->m[3] = pos;
    pm->m[0][3] = pm->m[1][3] = pm->m[2][3] = 0.0f;
    pm->m[3][3] = 1.0f;
    return pm;
}
