// func_00206170 (0x206170): a guard's deferred start (queued by PostStepguardLoad): its vt slot 26 with 0, then its splice
// message 0xE with one argument (0). The classes below only give the vtable layout (slot 3 the message handler).
class OBase { public: int a, b, c; virtual void V1(); virtual void V2(); virtual void Msg(int msg, int fSplice, int cpv, void **apv, int x); };
class O : public OBase { public: virtual void V4(); virtual void V5(); virtual void V6(); virtual void V7(); virtual void V8(); virtual void V9();
 virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15(); virtual void V16();
 virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
 virtual void V24(); virtual void V25(); virtual void V26(int nArg); };
extern "C" void func_00206170(O *pguard)
{
    int nArg;
    void *apv[1];
    pguard->V26(0);
    nArg = 0;
    apv[0] = &nArg;
    pguard->Msg(0xE, 1, 1, apv, 0);
}
