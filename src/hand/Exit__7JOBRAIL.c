/* JOBRAIL::Exit (AIJOB vt slot 9): the base exit, no rail state, the guard's state 0x1B removed. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetRailState(JOBRAIL *pjob, int st) asm("SetRailState__7JOBRAILi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBRAIL::Exit)
void Exit__7JOBRAIL(JOBRAIL *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetRailState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x1B);
}
