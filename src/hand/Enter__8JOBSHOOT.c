/* JOBSHOOT::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBSHOOT {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetShootState(struct JOBSHOOT *pjob, int n) asm("SetShootState__8JOBSHOOTi");

// name: SafeHouse port (JOBSHOOT::Enter)
void Enter__8JOBSHOOT(struct JOBSHOOT *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetShootState(pjob, 0);
}
