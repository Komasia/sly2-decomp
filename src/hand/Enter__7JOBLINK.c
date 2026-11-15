/* JOBLINK::Enter (AIJOB vt slot 8): the base enter, the job locked, and on to the link's first record. */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void LockJob(AIJOB *pjob) asm("LockJob__FP5AIJOB");
void NextRecord(JOBLINK *pjob) asm("NextRecord__7JOBLINK");

// name: SafeHouse port (JOBLINK::Enter)
void Enter__7JOBLINK(JOBLINK *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    LockJob(&pjob->aijob);
    NextRecord(pjob);
}
