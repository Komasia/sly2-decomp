/* JOBSHOOT::Exit (AIJOB vt slot 9): the base exit, then no shot state. */
#include "h2_aijobs.h"

void Exit__5AIJOB(AIJOB *pjob);
void SetShootState(JOBSHOOT *pjob, int st) asm("SetShootState__8JOBSHOOTi");

// name: SafeHouse port (JOBSHOOT::Exit)
void Exit__8JOBSHOOT(JOBSHOOT *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetShootState(pjob, SHOOTS_None);
}
