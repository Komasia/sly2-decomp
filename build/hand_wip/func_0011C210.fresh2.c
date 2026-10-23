typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { qword r[3]; } M3;
typedef struct { float m[4][4]; } M4;
#define ROW(i) { U s; qword r; \
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(pg[i])); \
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(pmat->r[i]), "j"(s.q)); \
    *(qword *)pm->m[i] = r; }
M4 *func_0011C210(M4 *pm, qword pos, M3 *pmat, int *pg)
{
    ROW(0) ROW(1) ROW(2)
    *(qword *)pm->m[3] = pos;
    pm->m[0][3] = pm->m[1][3] = pm->m[2][3] = 0.0f;
    pm->m[3][3] = 1.0f;
    return pm;
}
