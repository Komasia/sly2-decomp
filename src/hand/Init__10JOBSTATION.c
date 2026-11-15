/* JOBSTATION::Init (AIJOB vt slot 7): a guard keeping to a station object; no state yet, the guard gets state 0x26.
 * Layout: SafeHouse port (aijobs.h JOBSTATION). */
#include "h2_aijobs.h"

void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBSTATION::Init)
void Init__10JOBSTATION(JOBSTATION *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = STATS_None;
    AddGuardState(pjob->aijob.pguard, 0x26);
}
