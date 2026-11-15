/* JOBB0::Exit (AIJOB vt slot 9): the job exits, no held state, the guard's state 0x16 (held) removed. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetState(JOBB0 *pjob, int st) asm("SetState__5JOBB0i");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBB0::Exit)
void Exit__5JOBB0(JOBB0 *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetState(pjob, HELDS_None);
    RemoveGuardState(pjob->aijob.pguard, 0x16);
}
