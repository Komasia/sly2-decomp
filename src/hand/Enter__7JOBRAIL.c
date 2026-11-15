/* JOBRAIL::Enter (AIJOB vt slot 8): the base enter, then the rail's state 0. Layout: SafeHouse port (aijobs.cpp). */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void SetRailState__7JOBRAILi(JOBRAIL *pjob, int st);

// name: SafeHouse port (JOBRAIL::Enter)
void Enter__7JOBRAIL(JOBRAIL *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetRailState__7JOBRAILi(pjob, 0);
}
