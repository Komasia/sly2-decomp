// laneK6v1 (Claude agent, lane K6, 2026-10-24): laneK5v1 + a VU_FLOAT(const float *) ctor whose word input has a never-chosen "V" alternative ("r,V", 14F110 trick), used for k(&D_002BDA60): aligned 22 -> 20. Left: k/c/dt still vf5/vf4/vf3 (target vf3/vf5/vf6) and the target interleaves the lwc1/lw loads with the qmtc2s. No gain: non-volatile ctors (27-28), gdt read before k (20).
// laneK5v1 (Claude agent, lane K5, 2026-10-24): v3 + never-chosen "V" alternatives on the p14->pos inputs of Sub and AddScaled2 ("j,V", const-ref): p14->pos stays a MEM until reload, so it is reloaded twice off one p14 register (lqc2 0x20(a0) x2) like the target. Aligned still 22 (positional 52 -> 28). Left: k/c/dt get vf5/vf4/vf3 (target vf3/vf5/vf6, reloads vf4) and the loads do not cross the volatile qmtc2 ctors; non-volatile ctor 29, + non-volatile Sub 28.
// v3 (Claude agent, lane D5): aligned 24 -> 22. One commented register pin in the n4CC != 9 branch (Zero() into vf1 = pos, then vmove to v), as in the target. Left: the spring block (target reloads p14->pos for AddScaled2; VU_FLOAT qmtc2/sqc2 interleaving).
// NEAR MISS (Claude agent): 30/179. Joystick / random-target camera spring (func_00151340). Remaining: VU_FLOAT k/c/dt scheduling + target reloads
// p14->pos for the final AddScaled2 (CSE merges ours), vf register numbering in the spring block, n4CC==9-else path vsub into vf3 instead of vf1.
// Keys found: GClampR (return-style) for x, in-place GClamp for y; sx * clamp in the decl; u.q = Make(); pos = u.q (keeps pos in vf1);
// t = clock.t read before the 3rd GRand; VU_FLOAT ctor with "r"(*(int*)&f) (lw for k).
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
static inline float GClampR(float g, float lo, float hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }
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
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } VU_FLOAT(const float *pg) { __asm__ __volatile__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,V"(*(const int *)pg)); } /* never-chosen "V" alternative: allocation-only */ };
static inline qword Sub(qword a, const qword &b) { qword d; __asm__ __volatile__("vsub.xyzw %0, %1, %2" : "=j,j"(d) : "j,j"(a), "j,V"(b)); return d; } /* never-chosen "V" alternative: allocation-only */
static inline qword Combo(qword a, VU_FLOAT fa, qword b, VU_FLOAT fb)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %2x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a), "j"(fa.q), "j"(b), "j"(fb.q));
    return r;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword AddScaled2(const qword &a, qword b, qword c, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %4x\n\tvmaddx.xyzw %0, %3, %4x" : "=j,j"(r) : "j,V"(a), "j,j"(b), "j,j"(c), "j,j"(s.q)); /* never-chosen "V" alternative: allocation-only */
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
        float ax = sx * GClampR(GFromClq(D_002BDA10, __builtin_fabsf(pjoy->x)), D_002BDA20.gMin, D_002BDA20.gMax);
        float ay = GClamp(GFromClq(D_002BDA30, __builtin_fabsf(pjoy->y)), D_002BDA40.gMin, D_002BDA40.gMax);
        float y = sy * ay;
        v = Zero();
        union { qword q; } u;
        u.q = Make(0.0f, y, ax);
        pos = u.q;
    } else if (p->pgs->n4CC != 9) {
        register qword z asm("vf1"); /* register pin: target zeroes vf1 (pos) and copies it to v */
        z = Zero();
        pos = z;
        v = pos;
    } else {
        if (p->g18 < D_002DDED0.t) {
            float y = GRand(D_002BDA48);
            float z = GRand(D_002BDA50);
            float *pf = p->pos.f;
            pf[0] = 0.0f;
            pf[1] = y;
            pf[2] = z;
            float t = D_002DDED0.t;
            p->g18 = t + GRand(D_002BDA58);
        }
        VU_FLOAT k(&D_002BDA60);
        VU_FLOAT c(-D_002BDA64);
        float gdt = D_002DDED0.dt;
        VU_FLOAT dt(gdt);
        qword a = Combo(Sub(p->pos.q, p->p14->pos), k, p->v, c);
        v = AddScaled(p->v, a, dt);
        pos = AddScaled2(p->p14->pos, p->v, v, VU_FLOAT(gdt * 0.5f));
    }
    func_0012D108(p->p14, pos);
    p->v = v;
    func_0014E168(&D_002DDF40, &p->p10->m40);
}
