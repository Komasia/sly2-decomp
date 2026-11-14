struct RIP { char pad[0x14]; float t14; float g18; };
#include "clock.h"
void ForceRipFade(RIP *prip, float dt)
{
    float t = prip->g18 - (g_clock.t - prip->t14);
    if (dt < t) {
        float u = t / prip->g18;
        prip->g18 = dt / u;
        prip->t14 = g_clock.t - (1.0f - u) * prip->g18;
    }
}
