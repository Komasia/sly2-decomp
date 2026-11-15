/* JOBB2::Exit (AIJOB vt slot 9): the base exit, no state, the guard's state 0x20 removed. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetB2State(JOBB2 *pjob, int st) asm("SetB2State__5JOBB2i");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBB2::Exit)
void Exit__5JOBB2(JOBB2 *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetB2State(pjob, B2S_None);
    RemoveGuardState(pjob->aijob.pguard, 0x20);
}
