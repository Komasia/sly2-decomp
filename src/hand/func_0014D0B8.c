typedef unsigned long ulong;
#include "clock.h"
extern char g_game[];
ulong func_0014D240(struct CLOCK *p);
void UpdateGameTimers__Fv(void *p);
static __inline__ float GClamp(float g, float gMin, float gMax)
{
    float r;
    if (g < gMin) r = gMin;
    else if (gMax < g) r = gMax;
    else r = g;
    return r;
}
// name: SafeHouse port (UpdateClock)
void UpdateClock__FP5CLOCKi(struct CLOCK *p, int fPaused)
{
    ulong tick = func_0014D240(p);
    float dt = GClamp((float)(tick - p->tickFrame) * 3.3908420e-9f, 1.0f / 60.0f, 1.0f / 30.0f);
    p->dtCm = dt * p->rtCm;
    p->tCm += p->dtCm;
    {
    float dt2 = dt * p->art[3];
    p->dtReal = dt2;
    if (!fPaused) {
        p->dt = dt2 * p->rt;
        p->t += p->dt;
        UpdateGameTimers__Fv(g_game);
    }
    }
    p->tickFrame = tick;
    p->tReal += p->dtReal;
}
