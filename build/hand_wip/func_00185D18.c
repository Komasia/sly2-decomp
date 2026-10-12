typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
typedef struct { float x, y, z; } VEC3;
extern int func_00185310(void *p, qword v, int n, VEC3 *pv3, qword *pq1, qword *pq2);
extern float D_002BE918;
static __inline__ qword Bc(float g)
{
    VU u;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    u.q = s;
    return s;
}
static __inline__ qword BcI(int g)
{
    VU u;
    qword s;
    __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(g));
    u.q = s;
    return s;
}
static __inline__ qword MAdd2(qword a, qword b, qword sb, qword c, qword sc)
{
    qword r;
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddax.xyzw ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
        : "=j"(r) : "j"(a), "j"(b), "j"(sb), "j"(c), "j"(sc));
    return r;
}
static __inline__ qword MAdd1(qword a, qword b, qword sb)
{
    qword r;
    __asm__("vadda.xyzw ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(sb));
    return r;
}
int func_00185D18(void *p, float g, float h, qword a, qword b, qword c, VEC3 *pv3, qword *pq1, qword *pq2)
{
    VEC3 v3;
    VU q1, q2;
    func_00185310(p, MAdd2(a, b, Bc(h), c, Bc((h * 0.5f) * h)), 0, &v3, &q1.q, &q2.q);
    *pv3 = v3;
    *pq1 = MAdd1(q1.q, q2.q, Bc(g));
    *pq2 = MAdd2(b, c, Bc(h), q2.q, BcI(*(int *)&D_002BE918));
    return 1;
}
