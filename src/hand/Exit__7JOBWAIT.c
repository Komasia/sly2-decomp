/* JOBWAIT::Exit (AIJOB vt slot 9): the wait state ended, the job exits, the guard's state 0x1E (waiting) removed. */
#include "h2_aijobs.h"

void SetWaitState(JOBWAIT *pjob, int st) asm("SetWaitState__7JOBWAITi");
void Exit__5AIJOB(AIJOB *pjob);
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBWAIT::Exit)
void Exit__7JOBWAIT(JOBWAIT *pjob)
{
    SetWaitState(pjob, WAITS_None);
    Exit__5AIJOB(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x1E);
}
