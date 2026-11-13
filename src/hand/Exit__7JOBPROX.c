/* JOBPROX::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBPROX {
    /* 0x00 */ AIJOB aijob;
};
void SetProxState(struct JOBPROX *pjob, int n) asm("SetProxState__7JOBPROXi");
void Exit__5AIJOB(AIJOB *pjob);
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBPROX::Exit)
void Exit__7JOBPROX(struct JOBPROX *pjob)
{
    SetProxState(pjob, -1);
    Exit__5AIJOB(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x25);
}
