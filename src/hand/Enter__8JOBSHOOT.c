/* JOBSHOOT::Enter (AIJOB vt slot 8): the base enter, then the shot starts. */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void SetShootState(JOBSHOOT *pjob, int st) asm("SetShootState__8JOBSHOOTi");

// name: SafeHouse port (JOBSHOOT::Enter)
void Enter__8JOBSHOOT(JOBSHOOT *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetShootState(pjob, SHOOTS_Shoot);
}
