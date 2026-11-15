/* JOBSTATION::Enter (AIJOB vt slot 8): the base enter, then going to the station. */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void SetState(JOBSTATION *pjob, int st) asm("SetState__10JOBSTATIONi");

// name: SafeHouse port (JOBSTATION::Enter)
void Enter__10JOBSTATION(JOBSTATION *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetState(pjob, STATS_Going);
}
