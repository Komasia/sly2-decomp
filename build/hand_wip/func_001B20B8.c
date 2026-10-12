typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VT { short d; short pad; void *pfn; };
struct SMP { float a, b, c; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
struct Q { char pad[0xB0]; int xB0; };
struct P { char pad[0xC]; struct VT *vt; char pad1[0x58 - 0x10]; int x58; char pad2[0xE8 - 0x5C]; struct Q *pE8; char pad3[0x1E8 - 0xEC]; int x1E8;
           char pad4[0x270 - 0x1EC]; float g270; float g274; };
void *func_002333B4(void *p, int c, int cb);
float func_0011D018(float g, float gTarget, float dt, struct SMP *psmp, int n);
qword func_001FA810(void *p, int n, qword v);
void func_001FAC30(struct P *p, qword v);
static inline float Length(qword v)
{
    qword d, one;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}
static inline U Bcast(float g) { U u; __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(g)); return u; }
static inline qword VDiv(qword v, U s) { qword r; __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(s.q), "j"(v)); return r; }
static inline qword VMulX(qword v, U s) { qword r; __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q)); return r; }
static inline qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_001B20B8(struct P *p)
{
    qword v, n;
    float len, g;
    if (p->x1E8)
        return;
    v = ((qword (*)(void *))p->vt[33].pfn)((char *)p + p->vt[33].d);
    len = Length(v);
    n = VDiv(v, Bcast(len));
    {
        struct SMP smp;
        {
            struct SMP t;
            func_002333B4(&t, 0, sizeof(t));
            t.a = p->g274;
            t.c = 1.0f;
            smp = t;
        }
        g = func_0011D018(len, p->g270, D_002DDED0.dt, &smp, 0);
    }
    func_001FAC30(p, func_001FA810(&p->pE8->xB0, p->x58, VDiv(VSub(VMulX(n, Bcast(g)), v), Bcast(D_002DDED0.dt))));
}
