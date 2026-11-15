/* JOBB2::Init (0xB2): the guard's state 0x20 added; no state yet. */
#include "h2_aijobs.h"

void Init__5AIJOB(JOBB2 *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBB2::Init)
void Init__5JOBB2(JOBB2 *pjob)
{
    Init__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x20);
    pjob->st = B2S_None;
}
