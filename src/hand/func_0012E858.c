// (Claude agent) vmulx outputs into temps, then stores g, mT.r[0], mT.r[1] in that order.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
typedef struct { qword r[4]; } M4;
struct SO { char pad[0xE0]; struct SO *psoE0; char pad2[0x128 - 0xE4]; float g128; int x12C; };
struct P { char pad[0x10]; struct SO *pso; };
extern char g_cm[];
qword func_001A62E8(struct SO *pso);
M3 *func_001A6318(struct SO *pso);
void SetCmLookAt__FP2CMG9VU_VECTORT1ff(void *pcm, qword a, qword b, float g, float h);
void func_00256D18(qword *p, qword v);
void SetCmPosMat__FP2CMP6VECTOR(void *pcm, M4 *pm);
float func_00244B68(float g);
void SetCmFov__FP2CMf(void *pcm, float g);
static __inline__ void LoadM4(M4 *pm, M3 *pmat)
{
    pm->r[0] = pmat->r[0];
    pm->r[1] = pmat->r[1];
    pm->r[2] = pmat->r[2];
}
static __inline__ float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }

// name: SafeHouse port (CPLOOKAT::Update)
void Update__8CPLOOKATP6CPDEFIP5CMJOY(struct P *p)
{
    struct SO *pso = p->pso;
    if (pso->psoE0) {
        qword a = func_001A62E8(pso);
        qword b = func_001A62E8(pso->psoE0);
        SetCmLookAt__FP2CMG9VU_VECTORT1ff(g_cm, a, b, 0.0f, 0.0f);
    } else {
        M3 m = *func_001A6318(pso);
        M3 mT;
        M4 m4;
        U g;
        float f = -1.0f;
        M4 *pm = &m4;
        qword pos;
        {
        register qword gq __asm__("vf2");
        qword t1, t0;
        __asm__("qmtc2.ni %1, %0" : "=j"(gq) : "r"(f));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(t1) : "j"(m.r[0]), "j"(gq));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(t0) : "j"(m.r[2]), "j"(gq));
        g.q = gq;
        mT.r[0] = t0;
        mT.r[1] = t1;
        }
        mT.r[2] = m.r[1];
        pos = func_001A62E8(pso);
        func_00256D18(&m4.r[3], pos);
        LoadM4(pm, &mT);
        ((int *)&m4.r[2])[3] = 0;
        ((int *)&m4.r[1])[3] = 0;
        ((int *)&m4.r[0])[3] = 0;
        ((float *)&pm->r[3])[3] = 1.0f;
        SetCmPosMat__FP2CMP6VECTOR(g_cm, pm);
    }
    if (pso->x12C > 0) {
        float g = func_00244B68(17.995901107788086f / pso->g128);
        g = GClamp(g + g, 0.01f, 3.0f);
        SetCmFov__FP2CMf(g_cm, g);
    }
}
