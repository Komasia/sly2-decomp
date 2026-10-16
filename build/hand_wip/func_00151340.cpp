// NEAR MISS (Claude agent): 78/179. Joystick/random-target camera spring. Remaining: pos pseudo lands in a GPR (target keeps it in vf1, qmtc2 after Make),
// first clamp shape (target: r=min; if(!(x<min)){r=x; if(max<x) r=max}), sx/sy FPR numbers, p14->pos reload before Combo, GRand store order.
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern "C" CLOCK D_002DDED0;
struct CM;
extern "C" CM D_002DDF40;
struct CLQ { float g0, g1, g2, pad; };
struct LM { float gMin, gMax; };
extern "C" CLQ D_002BDA10;
extern "C" LM D_002BDA20;
extern "C" CLQ D_002BDA30;
extern "C" LM D_002BDA40;
extern "C" LM D_002BDA48, D_002BDA50, D_002BDA58;
extern "C" float D_002BDA60, D_002BDA64;
struct JOY { char pad[0x1070]; float x; float y; float g; };
struct GS { char pad[0x4CC]; int n4CC; };
struct TGT { char pad[0x20]; qword pos; };
struct OBJ { char pad[0x40]; int m40; };
struct X {
    GS *pgs; int pad4[3]; OBJ *p10; TGT *p14; float g18; int pad1C;
    union { qword q; float f[4]; } pos; qword v;
};
extern "C" {
void func_0014FD40(X *p, void *pv, JOY *pjoy);
float func_0011D448(float gMin, float gMax);
void func_0012D108(TGT *p, qword pos);
void func_0014E168(CM *p, int *pm);
void func_00151340(X *p, void *pv, JOY *pjoy);
}
static inline float GFromClq(const CLQ &c, float g) { return c.g0 + g * (c.g1 + g * c.g2); }
static inline float GLimitLm(LM *plm, float g)
{
    if (g < plm->gMin) return plm->gMin;
    if (g > plm->gMax) return plm->gMax;
    return g;
}
static inline float GClamp(float g, float lo, float hi) { if (g < lo) g = lo; else if (g > hi) g = hi; return g; }
static inline float GRand(const LM &lm) { return func_0011D448(lm.gMin, lm.gMax); }
static inline qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__ __volatile__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
static inline qword Zero() { qword q; __asm__ __volatile__("vsub.xyzw %0, $vf0, $vf0" : "=j"(q)); return q; }
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } };
static inline qword Sub(qword a, qword b) { qword d; __asm__ __volatile__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Combo(qword a, VU_FLOAT fa, qword b, VU_FLOAT fb)
{
    qword r;
    __asm__ __volatile__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(fa.q), "j"(b), "j"(fb.q));
    return r;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__ __volatile__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword AddScaled2(qword a, qword b, qword c, VU_FLOAT s)
{
    qword r;
    __asm__ __volatile__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %4x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(b), "j"(c), "j"(s.q));
    return r;
}

void func_00151340(X *p, void *pv, JOY *pjoy)
{
    qword pos, v;
    func_0014FD40(p, pv, pjoy);
    if (0.0f < pjoy->g) {
        float sx, sy;
        sx = 1.0f;
        if (0.0f < pjoy->x)
            sx = -1.0f;
        sy = -1.0f;
        if (0.0f < pjoy->y)
            sy = 1.0f;
        float ax = GClamp(GFromClq(D_002BDA10, __builtin_fabsf(pjoy->x)), D_002BDA20.gMin, D_002BDA20.gMax);
        float ay = GClamp(GFromClq(D_002BDA30, __builtin_fabsf(pjoy->y)), D_002BDA40.gMin, D_002BDA40.gMax);
        v = Zero();
        union { qword q; } u;
        pos = Make(0.0f, sy * ay, sx * ax);
        u.q = pos;
    } else if (p->pgs->n4CC != 9) {
        pos = Zero();
        v = pos;
    } else {
        if (p->g18 < D_002DDED0.t) {
            float y = GRand(D_002BDA48);
            float z = GRand(D_002BDA50);
            float *pf = p->pos.f;
            pf[0] = 0.0f;
            pf[2] = z;
            pf[1] = y;
            p->g18 = D_002DDED0.t + GRand(D_002BDA58);
        }
        VU_FLOAT k(D_002BDA60);
        VU_FLOAT c(-D_002BDA64);
        float gdt = D_002DDED0.dt;
        VU_FLOAT dt(gdt);
        TGT *ptgt = p->p14;
        qword a = Combo(Sub(p->pos.q, ptgt->pos), k, p->v, c);
        v = AddScaled(p->v, a, dt);
        pos = AddScaled2(ptgt->pos, p->v, v, VU_FLOAT(gdt * 0.5f));
    }
    func_0012D108(p->p14, pos);
    p->v = v;
    func_0014E168(&D_002DDF40, &p->p10->m40);
}
