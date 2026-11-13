/* PostLoadDock: a dock's post-load: the hack object's base, then its 3 segments bound (into +0x1D0). */
struct LO;
struct HACKSO;
void PostLoadHackSoBase(struct LO *plo) asm("PostLoadHackSoBase__FP2LO");
void BindHackSegs(struct LO *plo, int cseg, void *pv) asm("BindHackSegs__FP2LOP6HACKSOPv");

// name: SafeHouse port (PostLoadDock)
void PostLoadDock__FP2LO(struct LO *plo)
{
    PostLoadHackSoBase(plo);
    BindHackSegs(plo, 3, (char *)plo + 0x1D0);
}
