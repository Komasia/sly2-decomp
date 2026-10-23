typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { qword r[3]; } M3;
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
};
extern "C" {
void func_0011B570(M3 *pm, qword v);
M3 *func_0011BC00(M3 *pr, M3 *pa, M3 *pb);
qword func_0011BFB8(M3 *pm);
}
static inline M3 Rot(qword v) return m
{
    func_0011B570(&m, v);
}
static inline qword VF(float g)
{
    U s;
    qword q;
    __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(g));
    s.q = q;
    return q;
}
static inline qword Scale(qword v, qword k)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k));
    return r;
}
static inline M3 Mul(const M3 &a, const M3 *pb) return m
{
    M3 t;
    qword r0, r1, r2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r0) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(pb->r[0]));
    t.r[0] = r0; m.r[0] = r0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r1) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(pb->r[1]));
    t.r[1] = r1; m.r[1] = r1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r2) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(pb->r[2]));
    t.r[2] = r2; m.r[2] = r2;
}
extern "C" void func_00117308(float dt, float t, float gScale, M3 *pmat0, qword w0, M3 *pmat1, qword w1, M3 *pmatOut, qword *pwOut);
void func_00117308(float dt, float t, float gScale, M3 *pmat0, qword w0, M3 *pmat1, qword w1, M3 *pmatOut, qword *pwOut)
{
    float u = t / dt;
    float v = 1.0f - u;
    if (pmatOut) {
        float u2 = u * u;
        float h2 = u2 * v;
        float u3 = u2 * u;
        M3 a, b, rel, rot;
        func_0011B570(&rot, Scale(w0, VF(u * v * v * dt)));
        a = Mul(rot, pmat0);
        func_0011B570(&rot, Scale(w1, VF(-h2 * dt)));
        b = Mul(rot, pmat1);
        func_0011BC00(&rel, &a, &b);
        qword w = func_0011BFB8(&rel);
        func_0011B570(&rot, Scale(w, VF(h2 * (3.0f - dt) + u3)));
        *pmatOut = Mul(rot, &a);
    }
    if (pwOut) {
        qword k;
        U ku;
        __asm__("mfc1 %0, %1" : "=r"(k) : "f"(u * (6.0f - u * 6.0f) / dt));
        ku.q = k;
        M3 rel;
        func_0011BC00(&rel, pmat0, pmat1);
        qword w = func_0011BFB8(&rel);
        float h = u * 3.0f;
        qword sc = VF(gScale);
        qword ka = VF(1.0f - u * (4.0f - h));
        qword kb = VF(u * (h + -2.0f));
        qword r;
        __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddax.xyzw $ACC, %3, %4x\n\tvmaddx.xyzw %0, %5, %6x"
                : "=j"(r) : "j"(w), "j"(k), "j"(w0), "j"(ka), "j"(w1), "j"(kb));
        *pwOut = Scale(r, sc);
    }
}
