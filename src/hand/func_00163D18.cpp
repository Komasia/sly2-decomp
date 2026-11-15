class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
#include "so.h"
class TASK : public OBase {
public:
    char pad[0x5C - 0x10];
    int idDialog;
    int fDialog;
    int cPlayed;
    char pad1[0x7C - 0x68];
    TASK *pjob;
    char pad2[0xA8 - 0x80];
    int cobje, aobje, csme, asme, oidChk;
    char pad3[0xC4 - 0xBC];
    LO *ploExit;
    char pad4[0xF4 - 0xC8];
    int nMode;
};
struct SW;
extern SW g_sw;
extern char g_game[];
extern char D_003DA0C0[];   /* the dialog queue */
extern "C" void SetTaskCur(SW *psw, TASK *p) asm("SetTaskCur__FP7TASKMGRP4TASK");
extern "C" void SetTaskChk(SW *psw, TASK *p) asm("SetTaskChk__FP7TASKMGRP4TASK");
extern "C" int FJobCur(TASK *p) asm("FJobCur__FP3JOB");
extern "C" void JobBegin(TASK *p) asm("JobBegin__FP3JOB");
extern "C" int func_001637E8(TASK *p);
extern "C" void func_001643B0(TASK *p);
extern "C" void BroadcastTaskEvent(void *pv, int n, TASK *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void ApplyTaskObjects(TASK *p, int n, int c, int a) asm("ApplyTaskObjects__FPviiT0");
extern "C" void ApplyTaskSms(TASK *p, int n, int c, int a, int b) asm("ApplyTaskSms__FPvT0iT0i");
extern "C" void func_001DA4B8(void *pv, int n, float g);
extern "C" void TriggerExit(LO *plo) asm("TriggerExit__FP4EXIT");
/* ActivateTaskNow: a task becomes current (and the checkpoint, when it has one), its job begins if not current;
 * when it applies changes: a play counted and saved, event 0x23 (task started), its "start" objects and goals, its
 * dialog (if any) queued, message 0x13, and its exit triggered. */
// name: SafeHouse port (ActivateTaskNow)
extern "C" void ActivateTaskNow__FP4TASK(TASK *p)
{
    SW *psw = &g_sw;
    SetTaskCur(psw, p);
    if (p->oidChk != -1)
        SetTaskChk(psw, p);
    if (p->pjob && !FJobCur(p->pjob))
        JobBegin(p->pjob);
    if (func_001637E8(p)) {
        p->cPlayed++;
        func_001643B0(p);
        BroadcastTaskEvent(g_game, 0x23, p);
        ApplyTaskObjects(p, 4, p->cobje, p->aobje);
        ApplyTaskSms(p, 4, p->csme, p->asme, p->nMode);
        if (p->idDialog != -1 && p->fDialog)
            func_001DA4B8(D_003DA0C0, p->idDialog, -1.0f);
        p->Msg(0x13, 0, 0, 0, 0);
        if (p->ploExit) {
            LO *plo = p->ploExit;
            int grfUpd = plo->grfUnk40;
            if ((grfUpd ^ 1) & 1)
                *(int *)grfUpd |= 0x100;
            else
                plo->grfUnk40 = grfUpd | 0x100;
            TriggerExit(p->ploExit);
        }
    }
}
