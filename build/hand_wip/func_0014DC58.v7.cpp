// v7 (Claude agent, lane D24): 15 -> 12. Transpose written as a statement macro sharing one function-scope `aa` and `i` across both loops (loop-1 counter now a3 like the target). Left: M3->M4 copy load order + VU_FLOATC copy reload reg (target a3, ours v0: reload picks the first free reg, so in the target's sched1 order the s copy store sits among the mT row copies), loop-1 pointer setup order, loop-2 extra daddu from the empty-asm pcm copy.
// v6 (Claude agent, lane D23): 32 -> 15. (1) GClampR reads gMin and gMax into locals first (the gMax load sits in the bc1f delay slot; fixes the dt f6 / gMax f5 registers). (2) VU_FLOAT ctor moves the float with an `mfc1` asm into a plain qword (no extra daddu). Left: M3->M4 copy load order in Build (r0 lq last; target first, probably because the target puts the VU_FLOATC copy in a3), VU_FLOATC copy qmfc2 a3 placed early in the target, loop-1 counter a2 (target a3) and pointer setup order, and loop 2 extra daddu from the empty-asm pcm copy.
// v5 (Claude agent, lane D20): 34 -> 32. The 2nd Transpose's dest comes from a pcm copy passed through a commented empty volatile asm, so gcse no longer PREs pcm+0xD0 into s7: s7 gone, frame 0x160 matches. Left: the copy costs `daddu v0,s3; addiu v0,v0,0xD0` (target one addiu), which shifts loop 2 and adds an alignment nop; loop 1 counter a2 (target a3). Non-volatile asm: 41 (hoisted); asm on aa itself: 34; asm on pcm + pn local: 76.
// v4 (Claude agent, lane D13): 45 -> 34. func_0011C168 declared as returning M4 (same ABI: hidden pointer in a0), `mT = func_0011C168(&pcm->m60, &mT);` (its return temp reuses the M3 temp at 0x40); VU_FLOAT ctor writes a plain qword then copies it (s stays a pseudo, spilled at 0xB0/0xC0); Scale takes a VU_FLOATC with a user copy ctor (by-value copies at 0x70 like the target); a/b as unions declared after the call, mProj declared after them. Left: extra s7 (pcm+0x200 kept across the 1st BuildFrustrum), VU_FLOAT spill slot 0xB0 vs 0xC0, the a3=s copy of the 2nd Scale.
// DRAFT (Claude agent): camera shake/projection update (logic complete, far from matching: frame 0x1B0 vs 0x160, stack slot sharing of M3/M4/vector temps and VU_FLOAT spill not reproduced; s7 extra).
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct CLQ { float g0, g1, g2, gPad; };
struct LM { float gMin, gMax; };
struct CM {
    char pad[0x40]; float g40; float g44; float g48; float g4C; float g50; char pad2[0x60 - 0x54];
    M4 m60; float aaN0[3][4]; float aaN1[3][4]; M4 m100; M4 m140; M4 m180; qword anormal0[4]; qword anormal1[4];
    char pad3[0x618 - 0x240]; float g618;
};
struct CLOCK { float t; };
extern "C" {
extern CLOCK D_002DDED0;
extern float D_002BD850;
extern float D_002BD854;
extern CLQ D_002BD860;
extern LM D_002BBB60;
extern qword D_002BD870;
extern qword D_002BD880;
extern qword D_002BD890;
extern qword D_002BD8A0;
extern qword D_002A2DE0;
float func_00245000(float g);
M3 func_0011B570(qword v);
void func_00256D18(qword *pv, qword v);
M4 func_0011C168(M4 *pmA, M4 *pmB);
void func_0011C448(M4 *pm, float a, float b, float c, float d, float e, float f);
void func_0014D8F8(M4 *pmA, M4 *pmB, M4 *pmOut);
void func_0011C2F0(M4 *pm, M4 *pmOut);
void BuildFrustrum(M4 *pmat, float gx, float gy, qword *anormal);
void func_0014E078(CM *pcm);
void func_0014DC58(CM *pcm);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { qword t; __asm__("mfc1 %0, %1" : "=r"(t) : "f"(f)); q = t; } };

struct VU_FLOATC { qword q; VU_FLOATC(const VU_FLOAT &f) : q(f.q) {} VU_FLOATC(const VU_FLOATC &o) : q(o.q) {} };
static inline qword Scale(qword v, VU_FLOATC s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline void Build(M4 *pm, M3 m, qword v)
{
    func_00256D18(&pm->r[3], v);
    pm->r[0] = m.r[0];
    pm->r[1] = m.r[1];
    pm->r[2] = m.r[2];
    ((float *)pm)[15] = 1.0f;
    ((float *)pm)[11] = 0.0f;
    ((float *)pm)[7] = 0.0f;
    ((float *)pm)[3] = 0.0f;
}
static inline float GFromClq(float g, CLQ *pclq) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static inline float GClampR(float g, LM *plm) { float gMin = plm->gMin, gMax = plm->gMax; if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
#define TRANSPOSE(AA, AN) { \
    float *a0 = (float *)&(AN)[0]; float *a1 = (float *)&(AN)[1]; float *a2 = (float *)&(AN)[2]; float *a3 = (float *)&(AN)[3]; \
    aa = (AA); \
    for (i = 0; i < 3; i++) { aa[i][0] = a0[i]; aa[i][1] = a1[i]; aa[i][2] = a2[i]; aa[i][3] = a3[i]; } }

void func_0014DC58(CM *pcm)
{
    float (*aa)[4];
    int i;
    float dt = D_002DDED0.t - pcm->g618;
    if (D_002BD850 < dt) {
        func_0014D8F8(&pcm->m60, &pcm->m100, &pcm->m140);
    } else {
        float g = GClampR(GFromClq(dt / D_002BD850, &D_002BD860), &D_002BBB60);
        VU_FLOAT s(func_00245000(dt * D_002BD854) * g);
        M4 mT;
        Build(&mT, func_0011B570(Scale(D_002BD880, s)), Scale(D_002BD870, s));
        mT = func_0011C168(&pcm->m60, &mT);
        union { qword q; float f[4]; } a, b;
        a.q = AddScaled(D_002A2DE0, D_002BD890, s);
        b.q = Scale(D_002BD8A0, s);
        M4 mProj;
        func_0011C448(&mProj, a.f[0] * 512.0f / (pcm->g40 * 4096.0f), a.f[1] * 224.0f / (pcm->g44 * 4096.0f),
                          b.f[0], b.f[1], pcm->g4C, pcm->g50);
        func_0014D8F8(&mT, &mProj, &pcm->m140);
    }
    func_0011C2F0(&pcm->m140, &pcm->m180);
    BuildFrustrum(&pcm->m60, pcm->g40, pcm->g44, pcm->anormal0);
    TRANSPOSE(pcm->aaN0, pcm->anormal0);
    BuildFrustrum(&pcm->m60, pcm->g40 * 7.93f, pcm->g44 * 18.1f, pcm->anormal1);
    {
        CM *p = pcm;
        __asm__ __volatile__("" : "+r"(p)); /* empty asm: hides pcm+0xD0 from gcse */
        TRANSPOSE(p->aaN1, pcm->anormal1);
    }
    func_0014E078(pcm);
}
