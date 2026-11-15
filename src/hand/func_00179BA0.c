/* JOBWAIT::Update: patrol until tPause, pause until tResume, idle when the patrol's script is done; held (standing)
 * while the guard is held still, back to the pause (or idle, without a patrol) after. Repeats while the state changes. */
#include "clock.h"
#include "h2_aijobs.h"

void Update__5AIJOB(JOBWAIT *pjob);
int func_00209098(struct GUARD *pguard);   /* SafeHouse port: FGuardStill (0x209098) */
int FJobDone(JOBWAIT *pjob) asm("FJobDone__FP5AIJOB");
void SetWaitState__7JOBWAITi(JOBWAIT *pjob, int st);
int func_00171458(struct AIJOB *pjobScript);   /* the patrol's JOBSCRIPT is done */

// name: SafeHouse port (JOBWAIT::Update)
void Update__7JOBWAIT(JOBWAIT *pjob)
{
    int fStill, st;
    Update__5AIJOB(pjob);
    fStill = func_00209098(pjob->aijob.pguard);
    while (!FJobDone(pjob)) {
        st = pjob->st;
        switch (st) {
        case WAITS_Pause:
            if (fStill) SetWaitState__7JOBWAITi(pjob, WAITS_Held);
            else if (g_clock.t > pjob->tResume) SetWaitState__7JOBWAITi(pjob, WAITS_Patrol);
            break;
        case WAITS_Idle:
            if (fStill) SetWaitState__7JOBWAITi(pjob, WAITS_Held);
            break;
        case WAITS_Patrol:
            if (fStill) SetWaitState__7JOBWAITi(pjob, WAITS_Held);
            else if (g_clock.t > pjob->tPause) SetWaitState__7JOBWAITi(pjob, WAITS_Pause);
            else if (func_00171458(pjob->aijob.pchild)) { pjob->pcmdlist = 0; SetWaitState__7JOBWAITi(pjob, WAITS_Idle); }
            break;
        case WAITS_Held:
            if (!fStill) {
                if (pjob->pcmdlist) SetWaitState__7JOBWAITi(pjob, WAITS_Pause);
                else SetWaitState__7JOBWAITi(pjob, WAITS_Idle);
            }
            break;
        }
        if (pjob->st != st) continue;
        break;
    }
}
