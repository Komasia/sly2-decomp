/* JOBLINK::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBLINK {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void LockJob(AIJOB *pjob) asm("LockJob__FP5AIJOB");
void NextRecord(struct JOBLINK *pjob) asm("NextRecord__7JOBLINK");

// name: SafeHouse port (JOBLINK::Enter)
void Enter__7JOBLINK(struct JOBLINK *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    LockJob(&pjob->aijob);
    NextRecord(pjob);
}
