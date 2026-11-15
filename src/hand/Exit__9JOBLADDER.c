/* JOBLADDER::Exit (AIJOB vt slot 9): the base exit, no state, the guard's state 0x27 removed. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetLadderState(JOBLADDER *pjob, int st) asm("SetLadderState__9JOBLADDERi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLADDER::Exit)
void Exit__9JOBLADDER(JOBLADDER *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetLadderState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x27);
}
