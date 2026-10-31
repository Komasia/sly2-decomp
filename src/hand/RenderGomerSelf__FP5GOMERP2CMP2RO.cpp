struct GOMER { char pad[0xE78]; int fE78; };
struct CM;
struct RO;
extern "C" void InitStepguard(GOMER *pgomer, CM *pcm, RO *pro) asm("InitStepguard__FP9STEPGUARD");
void RenderGomerSelf(GOMER *pgomer, CM *pcm, RO *pro)
{
    InitStepguard(pgomer, pcm, pro);
    pgomer->fE78 = 1;
}
