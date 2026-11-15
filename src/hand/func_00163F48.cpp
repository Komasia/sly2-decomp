class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
class TASK : public OBase {
public:
    char pad[0x5C - 0x10];
    int idDialog;
    int fDialog;
    char pad2[0xA8 - 0x64];
    int cobje, aobje, csme, asme;
    char pad3[0xF4 - 0xB8];
    int nMode;
};
struct SW;
extern SW g_sw;
extern char g_game[];
extern char D_003DA0C0[];
extern "C" void SetTaskCur(SW *psw, TASK *p) asm("SetTaskCur__FP7TASKMGRP4TASK");
extern "C" int func_001637E8(TASK *p);
extern "C" void BroadcastTaskEvent(void *pv, int n, TASK *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void ApplyTaskObjects(TASK *p, int n, int c, int a) asm("ApplyTaskObjects__FPviiT0");
extern "C" void ApplyTaskSms(TASK *p, int n, int c, int a, int b) asm("ApplyTaskSms__FPvT0iT0i");
extern "C" void func_001DA578(void *pv, int n);
/* DeactivateTask: a task stops being current; when it applies changes: event 0x24 (task ended), its "end"
 * objects and goals, its dialog dropped, message 0x14. */
// name: SafeHouse port (DeactivateTask)
extern "C" void DeactivateTask__FP4TASK(TASK *p)
{
    SetTaskCur(&g_sw, 0);
    if (func_001637E8(p)) {
        BroadcastTaskEvent(g_game, 0x24, p);
        ApplyTaskObjects(p, 5, p->cobje, p->aobje);
        ApplyTaskSms(p, 5, p->csme, p->asme, p->nMode);
        if (p->idDialog != -1 && p->fDialog)
            func_001DA578(D_003DA0C0, p->idDialog);
        p->Msg(0x14, 0, 0, 0, 0);
    }
}
