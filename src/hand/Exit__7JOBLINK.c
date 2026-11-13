/* JOBLINK::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBLINK {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetState(struct JOBLINK *pjob, int n) asm("SetState__7JOBLINKi");
void UnlockJob(AIJOB *pjob) asm("UnlockJob__FP5AIJOB");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLINK::Exit)
void Exit__7JOBLINK(struct JOBLINK *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetState(pjob, -1);
    UnlockJob(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x2C);
}
