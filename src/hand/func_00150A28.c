typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { qword r[4]; } q; M3 m3; float af[4][4]; } M4;
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct CM;
extern struct CM g_cm;
extern float D_003E1BE0;
extern char D_002BD9B8[], D_002BD9C8[], D_002BD9D8[], D_002BD9E8[], D_002BD9F8[];
extern char g_lmZeroOne[], g_lmNegOneOne[];
struct SND { char pad[0x4E]; short c4E; };
struct X {
    char pad0[0x18]; float g18; char pad1[0x20 - 0x1C];
    qword q20; qword q30; void *p40; char pad2[0x50 - 0x44];
    qword q50; qword q60; float g70; char pad3[0x80 - 0x74];
    qword q80; qword q90; float gA0; float gA4; float gA8; float gAC; float gB0; float gB4; float gB8; float gBC;
    struct SND *pC0;
};
void func_0014FD40(struct X *p);
float GSmooth__FfffP3SMPPf(void *p, float *pdg, float g, float gTarget, float dt);
float GLimitLm(void *p, float g) asm("GLimitLm__FP2LMf");
void SetPitch__4CSndiif(struct SND *p, float g);
void SetVolume__4CSndf(struct SND *p, float g);
void Resume__4CSnd(struct SND *p);
void Pause__4CSnd(struct SND *p);
qword PosSmooth(qword a, qword b, float g, void *p, int n);
void BuildEulerMatrix__FP6VECTORG9VU_VECTOR(M3 *pm, qword v);
void SmoothMatrix(M3 *a, M3 *b, void *p, M3 *out, int n, float g);
qword DecomposeEulerMatrix__FP7MATRIX3(M3 *pm);
float RadSmooth(void *p, int n, float a, float b, float c) asm("RadSmooth__FfffP3SMPPf");
qword *func_00256D18(qword *p, qword v);
void SetCmPosMat__FP2CMP6VECTOR(struct CM *p, M4 *m);
void SetCmFov__FP2CMf(struct CM *p, float g);
void DecomposeRotateMatrixPanTilt(M4 *pm, float *pa, float *pb) asm("DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1");
qword PosEye__6CPFREE(struct X *p);
qword PosFocus__6CPFREE(struct X *p);
void SetCmLookAt__FP2CMG9VU_VECTORT1ff(struct CM *p, qword a, qword b, float c, float d);

static __inline__ float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin) return gMin;
    if (gMax < g) return gMax;
    return g;
}

static __inline__ float GFrac(float g, float a, float b)
{
    if (a == b) return 0.0f;
    return (g - a) / (b - a);
}

// name: SafeHouse port (CPFREE::Update)
void Update__6CPFREEP6CPDEFIP5CMJOY(struct X *p)
{
    func_0014FD40(p);
    if (g_clock.dt == 0.0f)
        return;
    if (0.0f <= p->g18) {
        float g = GClamp(GSmooth__FfffP3SMPPf(D_002BD9B8, 0, p->gAC, p->g18, g_clock.dt), 0.0f, 1.0f);
        p->gB0 = (g - p->gAC) / g_clock.dt;
        p->gAC = g;
    }
    if (p->gB0 != 0.0f) {
        struct SND *ps = p->pC0;
        SetPitch__4CSndiif(ps, GLimitLm(g_lmNegOneOne, __builtin_fabsf(p->gB0)));
        ps = p->pC0;
        SetVolume__4CSndf(ps, GLimitLm(g_lmZeroOne, __builtin_fabsf(p->gB0) * 0.5f + 0.5f));
        if (p->pC0->c4E > 0)
            Resume__4CSnd(p->pC0);
    } else {
        if (p->pC0->c4E <= 0)
            Pause__4CSnd(p->pC0);
    }
    if (p->p40) {
        M3 m0, m30, m60, m90;
        M4 m4;
        float u;
        p->q50 = PosSmooth(p->q50, p->q80, g_clock.dt, D_002BD9C8, 0);
        BuildEulerMatrix__FP6VECTORG9VU_VECTOR(&m90, p->q60);
        m0 = m90;
        BuildEulerMatrix__FP6VECTORG9VU_VECTOR(&m90, p->q90);
        m30 = m90;
        SmoothMatrix(&m0, &m30, D_002BD9D8, &m60, 0, g_clock.dt);
        p->q60 = DecomposeEulerMatrix__FP7MATRIX3(&m60);
        p->g70 = RadSmooth(D_002BD9E8, 0, p->g70, p->gA0, g_clock.dt);
        {
        M4 *pm4 = &m4;
        func_00256D18(&pm4->q.r[3], p->q50);
        pm4->q.r[0] = m60.r[0];
        pm4->q.r[1] = m60.r[1];
        pm4->q.r[2] = m60.r[2];
        m4.af[2][3] = 0.0f;
        m4.af[1][3] = 0.0f;
        m4.af[0][3] = 0.0f;
        pm4->af[3][3] = 1.0f;
        SetCmPosMat__FP2CMP6VECTOR(&g_cm, pm4);
        SetCmFov__FP2CMf(&g_cm, p->g70);
        DecomposeRotateMatrixPanTilt(pm4, &p->gA4, &p->gA8);
        }
        p->gAC = GLimitLm(g_lmZeroOne, GFrac(p->g70, p->gB8, p->gBC));
    } else {
        float u = 1.0f - p->gAC;
        SetCmFov__FP2CMf(&g_cm, (1.0f - u) * p->gB8 + u * p->gBC);
        {
            qword a = p->q30;
            p->q30 = PosSmooth(a, PosEye__6CPFREE(p), g_clock.dt, D_002BD9F8, 0);
        }
        {
            qword a = p->q20;
            p->q20 = PosSmooth(a, PosFocus__6CPFREE(p), g_clock.dt, D_002BD9F8, 0);
        }
        SetCmLookAt__FP2CMG9VU_VECTORT1ff(&g_cm, p->q30, p->q20, 0.0f, 0.0f);
    }
    D_003E1BE0 = g_clock.t;
}
