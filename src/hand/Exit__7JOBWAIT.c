/* JOBWAIT::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBWAIT {
    /* 0x00 */ AIJOB aijob;
};
void SetWaitState(struct JOBWAIT *pjob, int n) asm("SetWaitState__7JOBWAITi");
void Exit__5AIJOB(AIJOB *pjob);
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBWAIT::Exit)
void Exit__7JOBWAIT(struct JOBWAIT *pjob)
{
    SetWaitState(pjob, -1);
    Exit__5AIJOB(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x1E);
}
