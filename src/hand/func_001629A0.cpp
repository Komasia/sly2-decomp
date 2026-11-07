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
    int f7c;
    int pad80, pad84, pad88;
    int f8c, f90, f94, f98;
    char pad2[0xF0 - 0x9C];
    int ff0;
};
struct G;
extern G g_sw;
extern char g_game[];
extern "C" void SetJobCur(G *pg, O *p) asm("SetJobCur__FP7TASKMGRP3JOB");
extern "C" int func_00162670(O *p);
extern "C" void func_00163460(O *p);
extern "C" void BroadcastTaskEvent(void *pv, int n, O *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void ApplyTaskObjects(O *p, int n, int c, int a) asm("ApplyTaskObjects__FPviiT0");
extern "C" void ApplyTaskSms(O *p, int n, int c, int a, int b) asm("ApplyTaskSms__FPvT0iT0i");
extern "C" void func_001629A0(O *p)
{
    SetJobCur(&g_sw, p);
    if (func_00162670(p)) {
        p->f7c++;
        func_00163460(p);
        BroadcastTaskEvent(g_game, 0x21, p);
        ApplyTaskObjects(p, 4, p->f8c, p->f90);
        ApplyTaskSms(p, 4, p->f94, p->f98, p->ff0);
        p->Msg(0x13, 0, 0, 0, 0);
    }
}
