// fresh15 (Claude agent, lane A12, 2026-10-23): aligned 7 -> 4 from fresh14: k stored in a `volatile qword kv` and read ONCE into a local `k = kv` right before the final asm. The k load is then a real insn (local pseudo), so local-alloc gives k vf5 and w vf6 like the target. Left: kv gets its stack slot at expand time (0x100, below the w0/w1 reload spill slots; target k is at 0x120, i.e. a reload spill slot of the GPR k plus a separate VF copy), kb/r vf4/vf3 swapped, and the ka/kb dead-store order.
// fresh14 (Claude agent, lane A10, 2026-10-23): aligned 11 -> 7 from fresh13: ONE commented pin (sc in vf2), final Scale with the output tied to sc ("0"(k)), kb computed before ka. Left: w/k get vf5/vf6 (target vf6/vf5), kb/r vf4/vf3 (target vf3/vf4), dead-store order. Pinning w to vf6 too: 10.
// fresh13 (Claude agent, lane A6): aligned 11, as fresh12, but `M3 us` for the gScale dead store puts ka/kb dead stores at 0x30 like the target. Left: VF numbering/schedule of the final vmulax block.
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
static inline qword ScaleT(qword v, qword k)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %0x" : "=j"(r) : "j"(v), "0"(k));
    return r;
}
static inline qword Scale(qword v, qword k)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(k));
    return r;
}
static inline void MulP(M3 *pm, const M3 &a, const M3 *pb)
{
    M3 t;
    qword r0, r1, r2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r0) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(pb->r[0]));
    t.r[0] = r0; pm->r[0] = r0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r1) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(pb->r[1]));
    t.r[1] = r1; pm->r[1] = r1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r2) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(pb->r[2]));
    t.r[2] = r2; pm->r[2] = r2;
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
        qword w;
        func_0011B570(&rot, Scale(w0, VF(u * v * v * dt)));
        MulP(&rel, rot, pmat0);
        a = rel;
        func_0011B570(&rot, Scale(w1, VF(-h2 * dt)));
        MulP(&rel, rot, pmat1);
        b = rel;
        func_0011BC00(&rel, &a, &b);
        w = func_0011BFB8(&rel);
        func_0011B570(&rot, Scale(w, VF(h2 * (3.0f - dt) + u3)));
        MulP(&rel, rot, &a);
        *pmatOut = rel;
    }
    if (pwOut) {
        volatile qword kv = VU_FLOAT(u * (6.0f - u * 6.0f) / dt).q;
        qword w;
        {
            M3 rel;
            func_0011BC00(&rel, pmat0, pmat1);
            w = func_0011BFB8(&rel);
        }
        float h = u * 3.0f;
        M3 us;
        register qword sc __asm__("vf2"); /* pin */
        __asm__("qmtc2.ni %1, %0" : "=j"(sc) : "r"(gScale));
        us.r[0] = sc;
        qword kb = VF(u * (h + -2.0f));
        qword ka = VF(1.0f - u * (4.0f - h));
        qword r, k = kv;
        __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddax.xyzw $ACC, %3, %4x\n\tvmaddx.xyzw %0, %5, %6x"
                : "=j"(r) : "j"(w), "j"(k), "j"(w0), "j"(ka), "j"(w1), "j"(kb), "j"(k));
        *pwOut = ScaleT(r, sc);
    }
}
