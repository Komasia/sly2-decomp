// func_001B20B8 (lane 5): matched. Smooths the speed of the object's velocity toward a goal speed with GSmooth
// (func_0011D018) and hands the resulting acceleration to func_001FAC30 (same shape as func_00137248).
// Trick: the last clock-dt broadcast must take the clock word as a memory operand ("rV" on *(int *)&dt), so reload emits
// `lw $s0, 4($s0)`; passing it through an int pseudo gave `lw $v0` instead. The union below shares the stack slot of the
// temporary SMP with the scalar broadcast, as in the original.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VT { short d; short pad; void *pfn; };
struct SMP { float a, b, c; };
struct CLOCK { float t; float dt; };
extern "C" struct CLOCK D_002DDED0;
struct SPS { qword v; int k; };
struct O;
struct Q { char pad[0xB0]; struct SPS xB0; };
struct P {
    char pad[0xC];
    struct VT *vt;
    char pad1[0x58 - 0x10];
    struct O *x58;
    char pad2[0xE8 - 0x5C];
    struct Q *pE8;
    char pad3[0x1E8 - 0xEC];
    int x1E8;
    char pad4[0x270 - 0x1EC];
    float g270;  // goal speed
    float g274;  // smoothing parameter
};
extern "C" void *func_002333B4(void *p, int c, int cb);
extern "C" float func_0011D018(float g, float gTarget, float dt, struct SMP *psmp, float *out);
extern "C" qword func_001FA810(struct SPS *p, struct O *other, qword v);
extern "C" void func_001FAC30(struct P *p, qword v);

static inline float Length(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline U Bcast(float g) return u
{
    qword q;
    __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(g));
    u.q = q;
}
// Broadcast a float that lives in memory. "rV" (register or offsettable memory) only steers register allocation:
// the clock word is loaded by reload straight into the register holding its address.
static inline qword BcastMem(const float &f, U &home)
{
    qword q;
    __asm__("qmtc2.ni %1,%0" : "=j"(q) : "rV"(*(int *)&f));
    home.q = q;
    return home.q;
}
static inline qword VDiv(qword v, qword s)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(s), "j"(v));
    return r;
}
static inline qword VMulX(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s));
    return r;
}
static inline qword VSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

extern "C" void func_001B20B8(struct P *p)
{
    qword v, n;
    float len, g;
    if (p->x1E8)
        return;
    v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);  // virtual slot 33: velocity
    len = Length(v);
    n = VDiv(v, Bcast(len).q);  // unit direction
    {
        struct SMP smp;
        union { struct SMP state; U scalar; } temporary;
        {
            func_002333B4(&temporary.state, 0, sizeof(temporary.state));
            temporary.state.a = p->g274;
            temporary.state.c = 1.0f;
            smp = temporary.state;
        }
        float dt = D_002DDED0.dt;
        g = func_0011D018(len, p->g270, dt, &smp, 0);
        func_001FAC30(p, func_001FA810(&p->pE8->xB0, p->x58,
                                       VDiv(VSub(VMulX(n, Bcast(g).q), v), BcastMem(D_002DDED0.dt, temporary.scalar))));
    }
}
