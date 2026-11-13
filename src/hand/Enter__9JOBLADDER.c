/* JOBLADDER::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBLADDER {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetLadderState(struct JOBLADDER *pjob, int n) asm("SetLadderState__9JOBLADDERi");

// name: SafeHouse port (JOBLADDER::Enter)
void Enter__9JOBLADDER(struct JOBLADDER *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetLadderState(pjob, 0);
}
