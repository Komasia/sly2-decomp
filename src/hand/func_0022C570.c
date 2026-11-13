struct WRE { char pad[0x64]; float x; };
struct WRE *PwreGetWrCircle(void *p, int a) asm("PwreGetWrCircle__FP2WR4ENSK");
float GetWrWavelength__FP2WRPf(void *p)
{
    struct WRE *pwre = PwreGetWrCircle(p, 1);
    if (pwre->x == 0.0f) return 0.0f;
    return 1.0f / pwre->x;
}
