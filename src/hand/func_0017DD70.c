/* JOBBD::Init: the base init, the guard state 0x2B, no state. */
#include "h2_aijobs.h"

void Init__5AIJOB(JOBBD *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBBD::Init)
void Init__5JOBBD(JOBBD *pjob)
{
    Init__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x2B);
    pjob->st = BDS_None;
}
