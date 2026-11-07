typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union U { qword q; float f[4]; };
struct PP {
    char pad[0x1A8]; float x1A8;
    char pad1[0x18C4 - 0x1AC]; void *x18C4;
    char pad2[0x1910 - 0x18C8]; qword x1910;
};
extern "C" {
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
void AccelAloPos(PP *p, qword q) asm("AccelAloPos__FP3ALOG9VU_VECTOR");
void BrakeAloRotation(PP *p, M3 *pm, float *pg) asm("BrakeAloRotation__FP3ALOP7MATRIX3Pf");
void UpdateSlyHangMotion(PP *p) asm("UpdateSlyHangMotion__FP3SLY");
}
M3 BuildRotateVectorsMatrix(qword a, qword b) asm("BuildRotateVectorsMatrix__FP7MATRIX3G9VU_VECTORT1");
M3 BuildRotateMatrixAxis(qword a, float g) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
extern qword g_normalZ;
extern float D_002BF548[];
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
// name: SafeHouse port (UpdateSlyHangMotion)
void UpdateSlyHangMotion(PP *p)
{
    U v, d;
    M3 m1, m2, m;
    AccelAloPos(p, p->x1910);
    qword a;
    __asm__("qmtc2.ni %1, %0" : "=j"(a) : "r"(PosOfLo(p->x18C4)));
    v.q = a;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(a) : "j"(a), "j"(PosOfLo(p)));
    d.q = a;
    m1 = BuildRotateVectorsMatrix(g_normalZ, a);
    m2 = BuildRotateMatrixAxis(g_normalZ, p->x1A8);
    m = Mul(m1, m2);
    BrakeAloRotation(p, &m, D_002BF548);
}
