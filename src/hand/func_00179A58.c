/* JOBWAIT::Init (0xAA): no wait state, no pause / resume time yet; the guard's state 0x1E (waiting) added. */
#include "h2_aijobs.h"

void Init__5AIJOB(JOBWAIT *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBWAIT::Init)
void Init__7JOBWAIT(JOBWAIT *pjob)
{
    Init__5AIJOB(pjob);
    pjob->st = WAITS_None;
    pjob->tPause = pjob->tResume = 3.40282346638528859812e+38f;
    AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x1E);
}
