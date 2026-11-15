/* JOBWAIT::SetWaitState: leaving the patrol saves the script's place; the child job ends; the new state starts its
 * child: pause / idle stand (JOBSTAND, the resume time drawn), the patrol runs the command list from the saved place
 * (JOBSCRIPT, the pause time drawn), held stands alarmed (JOBSTAND, nAnim 1). */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"
#include "h2_cmdlist.h"

/* a pushed child job, as seen through its vtable */
struct JOBVT { char pad0[0xC]; VTENT *vt; char pad10[0x3C - 0x10]; int nAnim; };
struct GUARD {
    /* 0x000 */ char pad0[0x2DC];
    /* 0x2dc */ SAVEDSCRIPT saved;      /* field: SafeHouse port (saved2DC) */
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
void Save__9JOBSCRIPTP11SAVEDSCRIPT(struct AIJOB *pjobScript, SAVEDSCRIPT *psaved);
void SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(struct JOBVT *pjobScript, struct CMDLIST *pcmdlist, int n, SAVEDSCRIPT *psaved);
void func_00179EF8(JOBWAIT *pjob);
void func_00179E80(JOBWAIT *pjob);


// name: SafeHouse port (JOBWAIT::SetWaitState)
void SetWaitState__7JOBWAITi(JOBWAIT *pjob, int st)
{
    if (st == pjob->st) return;
    if (pjob->st == WAITS_Patrol) Save__9JOBSCRIPTP11SAVEDSCRIPT(pjob->aijob.pchild, &pjob->aijob.pguard->saved);
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case WAITS_Pause: case WAITS_Idle:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        func_00179EF8(pjob);
        pjob->tPause = 3.40282346638528859812e+38f;
        break;
    case WAITS_Patrol:
        { struct JOBVT *pjobScript = func_00205438(pjob->aijob.pguard, CID_JOBSCRIPT); VTENT *pvte; SetTarget__9JOBSCRIPTP7CMDLISTiP11SAVEDSCRIPT(pjobScript, pjob->pcmdlist, 0, &pjob->aijob.pguard->saved); pvte = &pjobScript->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobScript, pvte)); }
        func_00179E80(pjob);
        pjob->tResume = 3.40282346638528859812e+38f;
        break;
    case WAITS_Held:
        { struct JOBVT *pjobStand = func_00205438(pjob->aijob.pguard, CID_JOBSTAND); VTENT *pvte; pjobStand->nAnim = 1; pvte = &pjobStand->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobStand, pvte)); }
        break;
    }
}
