/* JOBSTATION::Exit (AIJOB vt slot 9): the base exit, the guard's state 0x26 removed. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBSTATION::Exit)
void Exit__10JOBSTATION(JOBSTATION *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x26);
}
