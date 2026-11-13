/* JOBSHOOT::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct JOBSHOOT {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetShootState(struct JOBSHOOT *pjob, int n) asm("SetShootState__8JOBSHOOTi");

// name: SafeHouse port (JOBSHOOT::Exit)
void Exit__8JOBSHOOT(struct JOBSHOOT *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetShootState(pjob, -1);
}
