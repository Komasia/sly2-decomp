/* JOBLINK::Init (AIJOB vt slot 7): a guard crossing a link between navigation regions; no state yet and the guard
 * gets state 0x2C. Layout: SafeHouse port (aijobs.h JOBLINK). */
#include "h2_aijobs.h"

void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLINK::Init)
void Init__7JOBLINK(JOBLINK *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = LINKS_None;
    AddGuardState(pjob->aijob.pguard, 0x2C);
}
