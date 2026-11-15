class OBase { public: int a, b, c; virtual void V1(); virtual void V2(); virtual void Msg(int msg, int fSplice, int cpv, void **apv, int x); };   /* vt slot 3 */
class GUARD : public OBase { public: char pad[0x2C0 - 0x10]; unsigned long grfState; };
extern "C" unsigned long func_00207A20(int st);
extern "C" void SetGuardStateMask(GUARD *pguard, unsigned long grfState) asm("SetGuardStateMask__FP5GUARDUl");
/* RemoveGuardState (0x209970): removes state st from the guard's state mask and sends itself message 7 (-1, st). */
// name: SafeHouse port (RemoveGuardState)
extern "C" void RemoveGuardState__FP5GUARDi(GUARD *pguard, int st)
{
    int stNew;
    void *apv[2];
    SetGuardStateMask(pguard, pguard->grfState & ~func_00207A20(st));
    stNew = -1;
    apv[0] = &stNew;
    apv[1] = &st;
    pguard->Msg(7, 0, 2, apv, 0);
}
