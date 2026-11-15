/* JOBSURROUND::Exit (AIJOB vt slot 9): the base exit, no state, the guard's state 0x19 removed. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetSurroundState(JOBSURROUND *pjob, int st) asm("SetSurroundState__11JOBSURROUNDi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBSURROUND::Exit)
void Exit__11JOBSURROUND(JOBSURROUND *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetSurroundState(pjob, SURS_None);
    RemoveGuardState(pjob->aijob.pguard, 0x19);
}
