/* JOBMOVE::Exit (AIJOB vt slot 9): the base exit, the move's state 1 (ended), and the guard leaves the move's
 * animation state. Layout: SafeHouse port (aijobs.h JOBMOVE). */
#include "aijob.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetMoveState(JOBMOVE *pjob, int n) asm("SetMoveState__7JOBMOVEi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBMOVE::Exit)
void Exit__7JOBMOVE(JOBMOVE *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetMoveState(pjob, 1);
    RemoveGuardState(pjob->aijob.pguard, pjob->nAnim);
}
