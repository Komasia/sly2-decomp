struct CLOCK { float t; float dt; };
extern CLOCK D_002DDED0 asm("D_002DDED0");
struct SAI { int a; };
struct LOOP { char pad[0x1C]; int cframe; char pad1[0x34 - 0x20]; SAI sai; char pad2[0x50 - 0x38];
    float dtLoopMin; float dtLoopMax; float dtPauseMin; float dtPauseMax; float dframe; float iframe; float dtPause; float dtPauseRemaining; };
extern "C" int func_0011A1E8(SAI *psai);
extern "C" float GRandInRange(float gLow, float gHigh) asm("GRandInRange__Fff");
extern "C" float GModPositive(float g, float gMod) asm("GModPositive__Fff");
extern "C" void SetSaiIframe(LOOP *p, int iframe) asm("SetSaiIframe__FP3SAIi");
void UpdateLoop(LOOP *ploop, float dt)
{
    if (func_0011A1E8(&ploop->sai))
        return;

    if (ploop->cframe < 2)
        return;

    if (ploop->dtPauseRemaining > 0.0f)
    {
        ploop->dtPauseRemaining -= D_002DDED0.dt;
        return;
    }

    ploop->iframe += ploop->dframe * D_002DDED0.dt;

    if (ploop->iframe >= (float)ploop->cframe)
    {
        float rand1 = GRandInRange(ploop->dtLoopMin, ploop->dtLoopMax);
        ploop->dframe = (float)ploop->cframe / rand1;

        float rand2 = GRandInRange(ploop->dtPauseMin, ploop->dtPauseMax);
        ploop->dtPause = rand2;
        ploop->dtPauseRemaining = rand2;
    }

    ploop->iframe = GModPositive(ploop->iframe, (float)ploop->cframe);
    SetSaiIframe(ploop, (int)ploop->iframe);
}
