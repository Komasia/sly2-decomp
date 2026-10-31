struct CLOCK { float t; };
extern CLOCK g_clock asm("g_clock");
struct SAI { int a; };
struct CIRCLER { char pad[0x34]; SAI sai; char pad2[0x50 - 0x38]; float radsSpeed; float radius; float duCenter; float dvCenter; };
extern "C" int func_0011A1E8(SAI *psai);
extern "C" float RadNormalize(float rad) asm("RadNormalize__Ff");
extern "C" void CalculateSinCos(float rad, float *pgSin, float *pgCos) asm("CalculateSinCos__FfPfT1");
extern "C" void SetSaiDuDv(CIRCLER *p, float du, float dv) asm("SetSaiDuDv__FP3SAIff");
void UpdateCircler(CIRCLER *pcircler, float dt)
{
    if (func_0011A1E8(&pcircler->sai))
        return;

    float angle = RadNormalize(g_clock.t * pcircler->radsSpeed);

    float sinOut;
    float cosOut;
    CalculateSinCos(angle, &sinOut, &cosOut);

    sinOut = (sinOut * pcircler->radius) + pcircler->duCenter;
    cosOut = (cosOut * pcircler->radius) + pcircler->dvCenter;

    SetSaiDuDv(pcircler, sinOut, cosOut);
}
