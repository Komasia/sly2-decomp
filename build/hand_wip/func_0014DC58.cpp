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
void func_0011C168(M4 *pmOut, M4 *pmA, M4 *pmB);
void func_0011C448(M4 *pm, float a, float b, float c, float d, float e, float f);
void func_0014D8F8(M4 *pmA, M4 *pmB, M4 *pmOut);
void func_0011C2F0(M4 *pm, M4 *pmOut);
void BuildFrustrum(M4 *pmat, float gx, float gy, qword *anormal);
void func_0014E078(CM *pcm);
void func_0014DC58(CM *pcm);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("" : "=r"(q) : "0"(*(int *)&f)); } };

static inline qword Scale(qword v, VU_FLOAT s)
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
    M4 *pm = &pcm->m60;
    if (!(D_002BD850 < dt)) {
        func_0014D8F8(pm, &pcm->m100, &pcm->m140);
    } else {
        float g = GClampR(GFromClq(dt / D_002BD850, &D_002BD860), &D_002BBB60);
        VU_FLOAT s(func_00245000(dt * D_002BD854) * g);
        M4 mT;
        M4 mProj;
        union { M3 m3; M4 m4; struct { qword a; qword b; } v; float af[16]; } u;
        u.m3 = func_0011B570(Scale(D_002BD880, s));
        func_00256D18(&mT.r[3], Scale(D_002BD870, s));
        mT.r[0] = u.m3.r[0];
        mT.r[1] = u.m3.r[1];
        mT.r[2] = u.m3.r[2];
        ((float *)&mT)[15] = 1.0f;
        ((float *)&mT)[11] = 0.0f;
        ((float *)&mT)[7] = 0.0f;
        ((float *)&mT)[3] = 0.0f;
        func_0011C168(&u.m4, pm, &mT);
        mT = u.m4;
        u.v.a = AddScaled(D_002A2DE0, D_002BD890, s);
        u.v.b = Scale(D_002BD8A0, s);
        func_0011C448(&mProj, u.af[0] * 512.0f / (pcm->g40 * 4096.0f), u.af[1] * 224.0f / (pcm->g44 * 4096.0f),
                      u.af[4], u.af[5], pcm->g4C, pcm->g50);
        func_0014D8F8(&mT, &mProj, &pcm->m140);
    }
    func_0011C2F0(&pcm->m140, &pcm->m180);
    BuildFrustrum(pm, pcm->g40, pcm->g44, pcm->anormal0);
    Transpose(pcm->aaN0, pcm->anormal0);
    BuildFrustrum(pm, pcm->g40 * 7.93f, pcm->g44 * 18.1f, pcm->anormal1);
    Transpose(pcm->aaN1, pcm->anormal1);
    func_0014E078(pcm);
}
