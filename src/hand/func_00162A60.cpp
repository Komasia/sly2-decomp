class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
class O : public OBase {
public:
    char pad[0x7C - 0x10];
    O *f7c;
    char pad2[0x8C - 0x80];
    int f8c, f90, f94, f98;
    char pad3[0xF0 - 0x9C];
    int ff0;
};
struct W { int a, b, f8; char pad[0x38 - 0xC]; int f38; };
struct G { char pad[0x3B14]; O *f3b14; char pad2[0x3C88 - 0x3B18]; int f3c88; int f3c8c; };
extern G g_sw;
extern char g_game[];
extern "C" void SetJobCur(G *pg, O *p) asm("SetJobCur__FP7TASKMGRP3JOB");
extern "C" void func_00165E10(G *pg, O *p);
extern "C" W *func_00210B70();
extern "C" int func_00210A88();
extern "C" W *func_00210990(int n);
extern "C" int func_00162670(O *p);
extern "C" void BroadcastTaskEvent(void *pv, int n, O *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void ApplyTaskObjects(O *p, int n, int c, int a) asm("ApplyTaskObjects__FPviiT0");
extern "C" void ApplyTaskSms(O *p, int n, int c, int a, int b) asm("ApplyTaskSms__FPvT0iT0i");
static inline int FSame(W *pw1, W *pw2)
{
    if (pw1 == pw2) return 1;
    if (!pw1 || !pw2) return 0;
    return (pw1->f8 ^ pw1->f38) == (pw2->f8 ^ pw2->f38);
}
// name: SafeHouse port (DeactivateJob)
extern "C" void DeactivateJob__FP3JOB(O *p)
{
    SetJobCur(&g_sw, 0);
    if (g_sw.f3b14 && g_sw.f3b14->f7c && g_sw.f3b14->f7c == p)
        func_00165E10(&g_sw, 0);
    W *pw1 = func_00210B70();
    W *pw2 = func_00210990(func_00210A88());
    if (FSame(pw1, pw2)) {
        g_sw.f3c88 = 0x189;
        g_sw.f3c8c = -1;
    }
    if (func_00162670(p)) {
        BroadcastTaskEvent(g_game, 0x22, p);
        ApplyTaskObjects(p, 5, p->f8c, p->f90);
        ApplyTaskSms(p, 5, p->f94, p->f98, p->ff0);
        p->Msg(0x14, 0, 0, 0, 0);
    }
}
