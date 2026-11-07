typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct RANGE { float a; float b; };
extern struct RANGE D_002BD480;
extern struct RANGE D_002BD488;
extern struct RANGE D_002BD490;
extern struct RANGE D_002BD498;
extern struct RANGE D_002BD4A0;
extern char g_sw[];
extern char g_cm[];
struct E { int pad[2]; void *x8; };
struct Q { char pad[0xF0]; float *xF0; qword *xF4; };
struct O { char pad[0x50]; int x50; int x54; struct E *x58; struct Q *x5C; };
struct P { char pad[0x38]; struct O *p38; };
void *PloPlayerPo__FP2SW(void *);
qword PosOfLo__FP2LO(void *);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct Q *, qword, int, int, int, int, float *);
int func_0011D910(struct RANGE *, float);
qword ConvertCmWorldToScreen__FP2CMG9VU_VECTOR(void *, qword);
float sqrtf(float);

static inline float GRemap(struct RANGE *pr, float g)
{
    if (pr->a == pr->b)
        return 0.0f;
    return (g - pr->a) / (pr->b - pr->a);
}

// name: SafeHouse port (JOBCHASE::IBest)
int IBest__8JOBCHASE(struct P *p)
{
    int iBest = -1;
    int i = 0;
    float ag[1];
    void *pv = PloPlayerPo__FP2SW(g_sw);
    float gBest = -1.0f;
    NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(p->p38->x5C, PosOfLo__FP2LO(pv), 0, 0, 0, 0, ag);
    for (; i < p->p38->x54; i++) {
        float g, u1, u2, u3, s;
        VU v;
        struct E *pe = &p->p38->x58[i];
        if (!pe->x8)
            continue;
        g = ag[0] - p->p38->x5C->xF0[i];
        if (p->p38->x50 == 1)
            g = -g;
        if (func_0011D910(&D_002BD480, g))
            u1 = GRemap(&D_002BD480, g);
        else if (func_0011D910(&D_002BD488, g))
            u1 = 1.0f - GRemap(&D_002BD488, g);
        else
            u1 = 0.0f;
        v.q = ConvertCmWorldToScreen__FP2CMG9VU_VECTOR(g_cm, p->p38->x5C->xF4[i]);
        if (func_0011D910(&D_002BD490, v.f[2]))
            u2 = GRemap(&D_002BD490, v.f[2]);
        else if (func_0011D910(&D_002BD498, v.f[2]))
            u2 = 1.0f - GRemap(&D_002BD498, v.f[2]);
        else
            u2 = 0.0f;
        { float l2 = v.f[0] * v.f[0] + v.f[1] * v.f[1]; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(g) : "f"(l2)); }
        if (func_0011D910(&D_002BD4A0, g))
            u3 = 1.0f - GRemap(&D_002BD4A0, g);
        else
            u3 = 0.0f;
        s = u1 * 0.5f + u2 * 0.15f + u3 * 0.35f;
        if (gBest < s) {
            gBest = s;
            iBest = i;
        }
    }
    return iBest;
}
