/* JOBLADDER::Init (AIJOB vt slot 7): a guard climbing the ladder / pipe it is attached to; no state yet, the guard
 * gets state 0x27. Layout: SafeHouse port (aijobs.h JOBLADDER). */
#include "h2_aijobs.h"

void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLADDER::Init)
void Init__9JOBLADDER(JOBLADDER *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = -1;
    AddGuardState(pjob->aijob.pguard, 0x27);
}
