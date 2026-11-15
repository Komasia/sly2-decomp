class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
};
/* a JOB view (include/h2_task.h); for the checkpoint TASK only +0x7C (its job) is used */
class O : public OBase {
public:
    char pad[0x7C - 0x10];
    O *pjob;
    char pad2[0x8C - 0x80];
    int cobje, aobje, csme, asme;
    char pad3[0xF0 - 0x9C];
    int nMode;
};
struct WORLDREC { int a, b, f8; char pad[0x38 - 0xC]; int f38; };   /* a world record; f8 ^ f38 identifies it */
struct SW { char pad[0x3B14]; O *ptaskChk; char pad2[0x3C88 - 0x3B18]; int oidPoint; int n3C8C; };
extern SW g_sw;
extern char g_game[];
extern "C" void SetJobCur(SW *psw, O *p) asm("SetJobCur__FP7TASKMGRP3JOB");
extern "C" void SetTaskChk(SW *psw, O *p) asm("SetTaskChk__FP7TASKMGRP4TASK");
extern "C" WORLDREC *func_00210B70();
extern "C" int func_00210A88();
extern "C" WORLDREC *func_00210990(int n);
extern "C" int func_00162670(O *p);
extern "C" void BroadcastTaskEvent(void *pv, int n, O *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void ApplyTaskObjects(O *p, int n, int c, int a) asm("ApplyTaskObjects__FPviiT0");
extern "C" void ApplyTaskSms(O *p, int n, int c, int a, int b) asm("ApplyTaskSms__FPvT0iT0i");
static inline int FSame(WORLDREC *pwrec1, WORLDREC *pwrec2)
{
    if (pwrec1 == pwrec2) return 1;
    if (!pwrec1 || !pwrec2) return 0;
    return (pwrec1->f8 ^ pwrec1->f38) == (pwrec2->f8 ^ pwrec2->f38);
}
/* DeactivateJob: a job stops being current (and the checkpoint task, if it is the job's); in its own world the
 * reload point becomes 0x189; when it applies changes: event 0x22 (job ended), its "end" objects and goals, and
 * message 0x14. */
// name: SafeHouse port (DeactivateJob)
extern "C" void DeactivateJob__FP3JOB(O *p)
{
    SetJobCur(&g_sw, 0);
    if (g_sw.ptaskChk && g_sw.ptaskChk->pjob && g_sw.ptaskChk->pjob == p)
        SetTaskChk(&g_sw, 0);
    WORLDREC *pwrec1 = func_00210B70();
    WORLDREC *pwrec2 = func_00210990(func_00210A88());
    if (FSame(pwrec1, pwrec2)) {
        g_sw.oidPoint = 0x189;
        g_sw.n3C8C = -1;
    }
    if (func_00162670(p)) {
        BroadcastTaskEvent(g_game, 0x22, p);
        ApplyTaskObjects(p, 5, p->cobje, p->aobje);
        ApplyTaskSms(p, 5, p->csme, p->asme, p->nMode);
        p->Msg(0x14, 0, 0, 0, 0);
    }
}
