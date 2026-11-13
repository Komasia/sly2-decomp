/* JOBSURROUND::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBSURROUND {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetSurroundState(struct JOBSURROUND *pjob, int n) asm("SetSurroundState__11JOBSURROUNDi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBSURROUND::Exit)
void Exit__11JOBSURROUND(struct JOBSURROUND *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetSurroundState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x19);
}
