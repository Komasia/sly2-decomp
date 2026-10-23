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
struct VU_FLOAT { qword q; VU_FLOAT(float f) { qword t; __asm__("" : "=r"(t) : "0"(*(int *)&f)); q = t; } };

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
static inline float GClampR(float g, LM *plm) { if (g < plm->gMin) return plm->gMin; if (plm->gMax < g) return plm->gMax; return g; }
static inline void Transpose(float (*aa)[4], qword *anormal)
{
    float *a0 = (float *)&anormal[0];
    float *a1 = (float *)&anormal[1];
    float *a2 = (float *)&anormal[2];
    float *a3 = (float *)&anormal[3];
    int i;
    for (i = 0; i < 3; i++) {
        aa[i][0] = a0[i];
        aa[i][1] = a1[i];
        aa[i][2] = a2[i];
        aa[i][3] = a3[i];
    }
}

void func_0014DC58(CM *pcm)
{
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
    Transpose(pcm->aaN0, pcm->anormal0);
    BuildFrustrum(&pcm->m60, pcm->g40 * 7.93f, pcm->g44 * 18.1f, pcm->anormal1);
    Transpose(pcm->aaN1, pcm->anormal1);
    func_0014E078(pcm);
}
