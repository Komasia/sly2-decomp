/* JOBLADDER::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBLADDER {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetLadderState(struct JOBLADDER *pjob, int n) asm("SetLadderState__9JOBLADDERi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLADDER::Exit)
void Exit__9JOBLADDER(struct JOBLADDER *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetLadderState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x27);
}
