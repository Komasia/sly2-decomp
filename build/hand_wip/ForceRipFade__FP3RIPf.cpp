struct RIP { char pad[0x14]; float t14; float g18; };
struct CLOCK { float t; float dt; };
extern CLOCK D_002DDED0;
void ForceRipFade(RIP *prip, float dt)
{
    float t = prip->g18 - (D_002DDED0.t - prip->t14);
    if (dt < t) {
        float u = t / prip->g18;
        prip->g18 = dt / u;
        prip->t14 = D_002DDED0.t - (1.0f - u) * prip->g18;
    }
}
