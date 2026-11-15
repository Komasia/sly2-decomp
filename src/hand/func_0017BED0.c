/* JOBSURROUND::Init (0xB3): the guard's state 0x19 added; no state yet. */
#include "h2_aijobs.h"

void Init__5AIJOB(JOBSURROUND *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBSURROUND::Init)
void Init__11JOBSURROUND(JOBSURROUND *pjob)
{
    Init__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x19);
    pjob->st = SURS_None;
}
