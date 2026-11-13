/* JOBACT::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBACT {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetActState(struct JOBACT *pjob, int n) asm("SetActState__6JOBACTi");
void LockJob(AIJOB *pjob) asm("LockJob__FP5AIJOB");

// name: SafeHouse port (JOBACT::Enter)
void Enter__6JOBACT(struct JOBACT *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetActState(pjob, 0);
    LockJob(&pjob->aijob);
}
