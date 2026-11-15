/* FBootyDrawDelta: the booty's draw by state: carried (4) drawn at its scale, growing from 1 to the carried scale over
 * +0x180 s through the clamped polynomial D_002A4B30; on its stand (1) or thrown (5) the SO's own draw; flying (2, 3)
 * nothing. Layout: SafeHouse port (booty.h / booty.cpp). */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
typedef union { qword q; float f[4]; } VU;
#include "clock.h"
extern float D_002A4B30[];
struct RANGE { float a; float b; };
extern struct RANGE g_lmZeroOne;
struct BOOTY { char pad[0x170]; VU vecScaleCarried; float dtScale; int state; float tState; };   /* field: SafeHouse port (booty.cpp) */
void RenderSoSelf__FP2SOP2CMP2RO(struct BOOTY *);
qword PosOfLo__FP2LO(void *);
void *MatJtLo__FP2LO(void *);
M4 func_0011C210(qword, void *, VU *);
void AppendAloExtraDraws__FP5SCENEP3ALOff(struct BOOTY *, M4 *, float, float);

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
void FBootyDrawDelta__FP3ALO(struct BOOTY *pbooty)
{
    switch (pbooty->state) {
    case 4: {
        VU v;
        M4 m;
        M4 mT;
        float dt = g_clock.t - pbooty->tState;
        if (pbooty->dtScale <= dt) {
            v = pbooty->vecScaleCarried;
        } else {
            float u = dt / pbooty->dtScale;
            float g = GClamp(D_002A4B30[0] + u * (D_002A4B30[1] + u * D_002A4B30[2]), g_lmZeroOne.a, g_lmZeroOne.b);
            int i;
            for (i = 0; i < 3; i++)
                v.f[i] = (1.0f - g) + g * pbooty->vecScaleCarried.f[i];
        }
        mT = func_0011C210(PosOfLo__FP2LO(pbooty), MatJtLo__FP2LO(pbooty), &v);
        m = mT;
        AppendAloExtraDraws__FP5SCENEP3ALOff(pbooty, &m, 1.0f, 1.0f);
        break;
    }
    case 1:
    case 5:
        RenderSoSelf__FP2SOP2CMP2RO(pbooty);
        break;
    case 2:
    case 3:
        break;
    }
}
