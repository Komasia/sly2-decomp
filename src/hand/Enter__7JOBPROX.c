/* JOBPROX::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBPROX {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetProxState(struct JOBPROX *pjob, int n) asm("SetProxState__7JOBPROXi");

// name: SafeHouse port (JOBPROX::Enter)
void Enter__7JOBPROX(struct JOBPROX *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetProxState(pjob, 0);
}
