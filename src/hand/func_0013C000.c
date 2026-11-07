typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
typedef union { qword q; float f[4]; } VU;
struct CLOCK { float t; };
extern struct CLOCK g_clock;
extern float D_002A4B30[];
struct RANGE { float a; float b; };
extern struct RANGE g_lmZeroOne;
struct P { char pad[0x170]; VU v170; float x180; int x184; float x188; };
void RenderSoSelf__FP2SOP2CMP2RO(struct P *);
qword func_001A62E8(void *);
void *MatJtLo__FP2LO(void *);
M4 func_0011C210(qword, void *, VU *);
void AppendAloExtraDraws__FP5SCENEP3ALOff(struct P *, M4 *, float, float);

static inline float GClamp(float g, float gMin, float gMax)
{
    float r;
    if (g < gMin)
        r = gMin;
    else if (gMax < g)
        r = gMax;
    else
        r = g;
    return r;
}

// name: SafeHouse port (FBootyDrawDelta)
void FBootyDrawDelta__FP3ALO(struct P *p)
{
    switch (p->x184) {
    case 4: {
        VU v;
        M4 m;
        M4 mT;
        float dt = g_clock.t - p->x188;
        if (p->x180 <= dt) {
            v = p->v170;
        } else {
            float u = dt / p->x180;
            float g = GClamp(D_002A4B30[0] + u * (D_002A4B30[1] + u * D_002A4B30[2]), g_lmZeroOne.a, g_lmZeroOne.b);
            int i;
            for (i = 0; i < 3; i++)
                v.f[i] = (1.0f - g) + g * p->v170.f[i];
        }
        mT = func_0011C210(func_001A62E8(p), MatJtLo__FP2LO(p), &v);
        m = mT;
        AppendAloExtraDraws__FP5SCENEP3ALOff(p, &m, 1.0f, 1.0f);
        break;
    }
    case 1:
    case 5:
        RenderSoSelf__FP2SOP2CMP2RO(p);
        break;
    case 2:
    case 3:
        break;
    }
}
