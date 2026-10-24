// v12 (Claude agent, lane D38): aligned 13 -> 10. v11 plus DotAfter for b = 2*Dot(dir, dpos): the same fused dot asm with ONE extra operand "g"(c), so its vmul waits for the sub.s of c (target order mtc1 dd / vsub dir / sub.s c / vmul) without a barrier, and the 4.0 / 1e-4 constants still load early. Left: the "g" operand makes reload emit an extra `mfc1 v0,f0` (not in the target; "f"/"X" give no copy but 17), 4.0/1e-4 in f2/f3 (target f3/f2), the 2nd Dot's one in vf3 (target vf4), the Dot(dir,dir) qmfc2 / mul.s order, and a vsub/sqc2 swap at 0x14C92C. "f"(dd) on the dir vsub: 31; "f"(c) there: 28.
// v11 (Claude agent, lane D36): aligned 21 -> 13. v8 + (1) clamp via locals t0/t1 with GMax(t0, 0.0f) (target min/max regs and store order), (2) `float a, b;` declared at function top (a/b get f4/f5 like the target), (3) SqrtF inline (sqrt.s asm with "=&f", as in matched DecomposeRotateMatrixRad/GetJoyXYDeflection) gives the target sqrt.s f0,f12 + mov.s f12,f0. Left: prologue schedule only (target: mtc1 dd before vsub dir, sub.s c before the Dot(dir,dpos) vmul, mtc1 b after Dot(dir,dir); one mtc1-hazard nop).
// v8 (Claude agent, lane D27): v7 (22) with Normalize reading D_002A2DA0 itself after VLen and the gl float made by a separate mtc1 asm (so reorg cannot pull the lq into the bc1f slot): lq a1 now after qmfc2 like the target (21). Left: sqrt.s f0,f12 + mov.s f12,f0; prologue Dot/sub.s order; min/max regs.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct LSG { qword apos[2]; qword anormal[2]; float au[2]; int lsgk; };
extern "C" {
extern qword D_002A2DA0;
void func_00119390(qword *pnormal, qword normal, qword pos);
int func_0014C748(qword posCenter, float sRadius, qword pos0, qword pos1, int clsgMax, LSG *alsg);
}

static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a > b ? a : b; }

static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

static inline float Dot(VU_VECTOR a, VU_VECTOR b)
{
    qword r, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(one) : "j"(a.q), "j"(b.q) : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}

static inline float DotAfter(VU_VECTOR a, VU_VECTOR b, float gAfter)
{
    qword r, one;
    float g;
    /* gAfter is an allocation-only operand */
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(one) : "j"(a.q), "j"(b.q), "g"(gAfter) : "memory");
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}

static inline qword SubV(VU_VECTOR a, VU_VECTOR b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a.q), "j"(b.q));
    return r;
}

static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}

static inline qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %1, %2, %2\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=j"(one), "=&j"(l) : "j"(c) : "memory");
    {
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(l));
    return r;
    }
}

static inline VU_VECTOR Normalize(qword d)
{
    qword l = VLen(d);
    qword k = D_002A2DA0;
    float gl;
    int il;
    __asm__("qmfc2.ni %0, %1" : "=r"(il) : "j"(l));
    __asm__("mtc1 %1, %0" : "=f"(gl) : "r"(il));
    if (gl < 1e-4f)
        return k;
    {
        qword r;
        __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(d), "j"(l));
        return r;
    }
}

int func_0014C748(qword posCenter, float sRadius, qword pos0, qword pos1, int clsgMax, LSG *alsg)
{
    float au[2];
    float a, b;
    if (clsgMax <= 0)
        return 0;
    qword dpos = Sub(pos0, posCenter);
    float c = Dot(dpos, dpos) - sRadius * sRadius;
    qword dir = Sub(pos1, pos0);
    b = 2.0f * DotAfter(dir, dpos, c);
    a = Dot(dir, dir);
    float disc = b * b - 4.0f * a * c;
    if (disc < 1e-4f)
        return 0;
    disc = SqrtF(disc);
    {
        float u0 = (-b - disc) / (2.0f * a);
        float u1 = (-b + disc) / (2.0f * a);
        au[0] = u0;
        au[1] = u1;
        if (u0 < 0.0f && u1 < 0.0f)
            return 0;
        if (u0 > 1.0f && u1 > 1.0f)
            return 0;
    }
    {
        float t0 = au[0];
        float t1 = au[1];
        t1 = GMin(1.0f, t1);
        t0 = GMax(t0, 0.0f);
        au[1] = t1;
        au[0] = t0;
    }
    for (int i = 0; i < 2; i++) {
        float u = au[i];
        alsg->au[i] = u;
        qword pos = VecCombo(VU_FLOAT(u), pos1, VU_FLOAT(1.0f - u), pos0);
        alsg->apos[i] = pos;
        func_00119390(&alsg->anormal[i], Normalize(SubV(pos, posCenter)).q, pos);
    }
    alsg->lsgk = 1;
    return 1;
}
