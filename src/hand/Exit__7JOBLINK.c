/* JOBLINK::Exit (AIJOB vt slot 9): the base exit, no state, the job unlocked and the guard state 0x2C gone. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetState(JOBLINK *pjob, int n) asm("SetState__7JOBLINKi");
void UnlockJob(AIJOB *pjob) asm("UnlockJob__FP5AIJOB");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLINK::Exit)
void Exit__7JOBLINK(JOBLINK *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetState(pjob, LINKS_None);
    UnlockJob(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x2C);
}
