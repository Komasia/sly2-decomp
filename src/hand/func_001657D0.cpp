class OBase {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void Msg(int msgid, int a, int c, void **apv, int d);
    virtual void V4(int msgid, void *pv);
};
class JOB;
class TASK : public OBase {
public:
    int f10;
    int f14;
    int oid;
    char pad[0x54 - 0x1C];
    int nState;
    float tState;
    char pad1[0x64 - 0x5C];
    int cPlayed;
    int cDone;
    char pad2[0x70 - 0x6C];
    int fActivate;      /* becoming available activates it */
    int fCurOnRestore;  /* in mode 1, available: it is the task manager's current task */
    char pad3[0x7C - 0x78];
    JOB *pjob;
    char pad4[0xA8 - 0x80];
    int cobje, aobje, csme, asme;
    char pad5[0xF4 - 0xB8];
    int nMode;
};
class JOB : public OBase {
public:
    char pad[0x64 - 0x10];
    TASK *ptaskFirst;
    char pad1[0x7C - 0x68];
    int cPlayed;
};
#include "clock.h"
#include "dl.h"
extern DL D_003E0F90;   /* the available tasks */
extern char g_game[];
extern int D_002DEB44;   /* the current task's oid */
extern "C" int func_001637E8(TASK *p);
extern "C" void BroadcastTaskEvent(void *pv, int nEvent, TASK *p) asm("BroadcastTaskEvent__FP2SWiP2LO");
extern "C" void RemoveDlEntry(DL *pdl, void *pv) asm("RemoveDlEntry__FP2DLPv");
extern "C" void AppendDlEntry(DL *pdl, void *pv) asm("AppendDlEntry__FP2DLPv");
extern "C" void ApplyTaskObjects(TASK *p, int nState, int c, int a) asm("ApplyTaskObjects__FPviiT0");
extern "C" void ApplyTaskSms(TASK *p, int nState, int c, int a, int b) asm("ApplyTaskSms__FPvT0iT0i");
extern "C" void func_001643B0(TASK *p);
extern "C" void func_00163C28(TASK *p);
extern "C" void func_00163CE0(TASK *p);
/* SetTaskState: set a task's state: events 0x26 / 0x25 and messages 0x16 / 0x15 around it, the available list
 * kept, its objects and goals for the new state, a reset (mode 4, locked) clears its counts, done (mode 0) counts
 * one, then it is saved; by mode, becoming available activates it (or makes it the current one, mode 1) and
 * locked / closed leaves it. */
// name: SafeHouse port (SetTaskState)
extern "C" void SetTaskState__FP4TASKi(TASK *p, int nState)
{
    if (p->nState == nState)
        return;
    if (func_001637E8(p)) {
        BroadcastTaskEvent(g_game, 0x26, p);
        p->Msg(0x16, 0, 0, 0, 0);
    }
    if (p->nState == 1)
        RemoveDlEntry(&D_003E0F90, p);
    if (func_001637E8(p)) {
        ApplyTaskObjects(p, nState, p->cobje, p->aobje);
        ApplyTaskSms(p, nState, p->csme, p->asme, p->nMode);
    }
    switch (nState) {
    case 0:
        if (p->nMode == 4) {
            p->cPlayed = 0;
            p->cDone = 0;
            if (p->pjob && p->pjob->ptaskFirst == p)
                p->pjob->cPlayed = 0;
        }
        break;
    case 1:
        AppendDlEntry(&D_003E0F90, p);
        break;
    case 2:
        if (p->nMode == 0)
            p->cDone++;
        break;
    }
    p->nState = nState;
    p->tState = g_clock.t;
    func_001643B0(p);
    if (func_001637E8(p)) {
        BroadcastTaskEvent(g_game, 0x25, p);
        p->Msg(0x15, 0, 0, 0, 0);
        p->V4(0x11, p);
    }
    switch (p->nMode) {
    case 1:
        if (p->nState == 1 && p->fCurOnRestore)
            D_002DEB44 = p->oid;
        break;
    case 0:
    case 2:
    case 4:
        switch (p->nState) {
        case 1:
            if (p->fActivate)
                func_00163C28(p);
            break;
        case 0:
        case 3:
            func_00163CE0(p);
            break;
        }
        break;
    case 3:
        break;
    }
}
