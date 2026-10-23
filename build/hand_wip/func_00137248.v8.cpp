// v8 (Claude agent laneB23, 2026-10-23): aligned 6 (7 insns differ, was 23). v7 plus: the M3 copy as an explicit `M3 mc; M3 m = func_0011B500(...); mc = m;` with MulM3 taking const M3 & (fixes the m 0x50 / copy 0x20 slots), and the len qmfc2 non-volatile with an allocation-only "r"(c) input (lui/addiu s0 now right). Left: len qmfc2 must come before the c qmfc2 (target v1, then mtc1 f12), lwc1 f13 D_002BC998 too early.
// v7 (Claude agent laneB23, 2026-10-23): aligned 16 -> 6. From the laneB22 "rV" probe (dt MEM input to the VU_FLOATM qmtc2) plus `M3 m = func_0011B500(...)` as an initializer instead of `M3 m; m = ...;` (the assignment made a 2nd m copy whose stores kept the rows live past the dv reload). Left: m (0x20) and the MulM3 by-value copy (0x50) swapped vs the target, and the lui/addiu s0 (&D_002DDED0) placement around the Cross.
// v6 (Claude agent laneB16, 2026-10-23): aligned 17 -> 16. Cross computed into a local first, then len via a VOLATILE qmfc2 (GetXV, emulates the target order: len qmfc2 after vopmsub). Left: the d0 vsub reads the 2nd func_001A62E8 result straight from v0 (combine merged the copy, reload picks vf5; target vf1 = a pseudo), lui s0 (&D_002DDED0) placement, final lw s0,4(s0).
// v5 (Claude agent laneB15, 2026-10-23): aligned 28 -> 17. Dot output without earlyclobber (target dot output reuses the n register), by-value DivF(Sub(MulM3(m, t), dv), VU_FLOATM(dt)) (laneB13 lead, non-volatile qmtc2), and MulM3 with an allocation-only repeat of m.r[0] (rows vf2/vf3/vf4 like the target). Left: first d0 sub reg (vf6 vs vf1), Cross/Dot schedule around qmfc2, final dt lw/qmtc2 placement (target lw s0,4(s0) before the MulM3, so the dv reload gets vf2 and vmulq vf3).
// v4 (Claude agent laneB11, 2026-10-23): aligned 29 -> 28. VU_FLOATM fdt built before the MulM3 with a VOLATILE qmtc2 asm: dt qmtc2 + m rows vf2/vf3/vf4 now like the target; but dv loads into vf6 early (target reloads it into vf2 after the MulM3) and the m-copy sqc2s move up. Volatile is a probe. vy pin to vf1 is ignored (copied).
// v3 (Claude agent laneB8, 2026-10-23): aligned 54 -> 29. (1) dv = Sub(p->GetVel(), py->GetVel()) with no vp local (dv gets 0x90, the GetVel temp 0xA0). (2) First n sub into a plain qword d0. (3) The len<0.0001 test as an inline SafeDiv(UQ &n, qlen, const qword &vDef): the reference arg hoists lui/addiu &D_002A2DA0 before the branch and both arms store n. (4) Scale operands swapped (output ties with the dot). (5) VU_FLOATM = qmtc2 from *(int *)&f. Left: py pos in vf4 (target vf1); final block dt lw/qmtc2 is scheduled before the MulM3 in the target, m rows vf2/vf3/vf4.
// v2 (Claude agent laneB7, 2026-10-23): aligned 67 -> 54. VU_FLOAT ctor = qmtc2 "=j" from "r"(f) (target sqc2 of the VF temp to 0x10); Length split into dot asm + vsqrt/vwaitq/vaddq asm; GetX = qmfc2 "=r"(float) so qlen stays in a VF reg (two qmfc2 like the target).
// wip (Claude agent): 111/166 - logic complete (orbit/relative-velocity steering); remaining: spill slots dv/vp swapped (0x90/0xA0), len mtc1 / dot scheduling, VU reg numbering.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union UQ { qword q; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VU_FLOATM {
    qword q;
    VU_FLOATM(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "rV"(*(int *)&f)); }
};
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot(qword a, qword b)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
        : "=j"(r), "=&j"(one) : "j"(a), "j"(b));
    return r;
}
static inline qword Length(qword a)
{
    qword r, t, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
        : "=&j"(t), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(t));
    return r;
}
static inline qword Scale(qword v, qword f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f), "j"(v));
    return r;
}
static inline qword DivQ(qword v, qword f)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(f));
    return r;
}
static inline qword DivF(qword v, VU_FLOATM f)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(f.q));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword AddScaled(qword a, qword v, VU_FLOAT f)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(f.q));
    return r;
}
static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v), "j"(m.r[0])); /* extra operand: allocation only */
    return r;
}
static inline float GetX(qword q)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(q));
    return f;
}
static inline float GetXV(qword q, qword c)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(q), "r"(c)); /* c: allocation only */
    return f;
}
static inline float GetZ(qword q)
{
    int i;
    float f;
    __asm__("pextuw %0, $0, %1" : "=r"(i) : "r"(q));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(i));
    return f;
}

static inline void SafeDiv(UQ &v, qword len, const qword &vDef)
{
    if (GetX(len) < 0.0001f)
        v.q = vDef;
    else
        v.q = DivQ(v.q, len);
}

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct BASE { int x0, x4, x8; };
struct P : BASE {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h)
    virtual qword GetVel();            /* 33 */
};
struct PX { char pad[0x10DC]; P *py; };
struct S { P *p; };
struct CLOCK { float t; float dt; };
struct SMP { float a, b, c; };
extern "C" {
extern CLOCK D_002DDED0;
extern float D_002BC998, D_002BC99C, D_002BC9A0;
extern SMP D_002BC9A8;
extern qword D_002A2DC0, D_002A2DA0;
qword func_001A62E8(P *p);
float func_0011D018(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext);
float func_0011CFE0(float g, float gMax);
M3 func_0011B500(qword axis, float g);
qword func_0011E9F8(qword v, float g);
void func_001FAC30(P *p, qword v);
}

extern "C" void func_00137248(S *s)
{
    P *p = s->p;
    P *py = ((PX *)p)->py;
    if (py == 0)
        return;
    float gMax = D_002BC99C * D_002BC99C / D_002BC998 + D_002BC9A0;
    qword dv = Sub(p->GetVel(), py->GetVel());
    UQ n;
    qword d0 = Sub(func_001A62E8(s->p), func_001A62E8(py));
    n.q = Sub(d0, Scale(D_002A2DC0, Dot(d0, D_002A2DC0)));
    qword qlen = Length(n.q);
    SafeDiv(n, qlen, D_002A2DA0);
    qword c = Cross(n.q, dv);
    float len = GetXV(qlen, c);
    float cz = GetZ(c);
    float dot = GetX(Dot(dv, n.q));
    float w = cz / len;
    float dgNext;
    func_0011D018(len, D_002BC998, D_002DDED0.dt, &D_002BC9A8, &dgNext);
    float g = func_0011CFE0(dgNext - dot, D_002BC9A0 * D_002DDED0.dt);
    qword t = AddScaled(dv, n.q, VU_FLOAT(g));
    M3 mc;
    M3 m = func_0011B500(D_002A2DC0, w * D_002DDED0.dt);
    mc = m;
    qword r = DivF(Sub(MulM3(mc, t), dv), VU_FLOATM(D_002DDED0.dt));
    func_001FAC30(s->p, func_0011E9F8(r, gMax));
}
