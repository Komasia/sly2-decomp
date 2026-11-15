// func_001629A0 (SafeHouse: ActivateJob): make the job current; when it applies its changes, count a play, save it,
// broadcast event 0x21 (job started), show its "start" objects and goals and send it message 0x13.
class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);   /* vtable entry 3: send a message */
};
class O : public OBase {
public:
    char pad[0x7C - 0x10];
    int cPlayed;
    int pad80, pad84, pad88;
    int cobje, aobje, csme, asme;
    char pad2[0xF0 - 0x9C];
    int nMode;
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
        p->cPlayed++;
        func_00163460(p);
        BroadcastTaskEvent(g_game, 0x21, p);
        ApplyTaskObjects(p, 4, p->cobje, p->aobje);   /* the start group */
        ApplyTaskSms(p, 4, p->csme, p->asme, p->nMode);
        p->Msg(0x13, 0, 0, 0, 0);
    }
}
