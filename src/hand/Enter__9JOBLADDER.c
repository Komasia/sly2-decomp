/* JOBLADDER::Enter (AIJOB vt slot 8): the base enter, then climbing. */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void SetLadderState(JOBLADDER *pjob, int st) asm("SetLadderState__9JOBLADDERi");

// name: SafeHouse port (JOBLADDER::Enter)
void Enter__9JOBLADDER(JOBLADDER *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetLadderState(pjob, 0);
}
