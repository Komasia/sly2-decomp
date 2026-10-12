struct GOMER { char pad[0xE78]; int fE78; };
struct CM;
struct RO;
extern "C" void func_00205EB8(GOMER *pgomer, CM *pcm, RO *pro);
void RenderGomerSelf(GOMER *pgomer, CM *pcm, RO *pro)
{
    func_00205EB8(pgomer, pcm, pro);
    pgomer->fE78 = 1;
}
