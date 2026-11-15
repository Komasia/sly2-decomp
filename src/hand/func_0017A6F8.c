/* JOBB0::Init (0xB0, held): the guard's state 0x16 (held) added; no held state yet. */
#include "h2_aijobs.h"

void Init__5AIJOB(JOBB0 *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBB0::Init)
void Init__5JOBB0(JOBB0 *pjob)
{
    Init__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x16);
    pjob->stHeld = HELDS_None;
}
