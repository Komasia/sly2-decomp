/* JOBRAIL::Enter (AIJOB vt slot 8): the base enter, then the rail's state 0. Layout: SafeHouse port (aijobs.cpp). */
#include "aijob.h"

struct JOBRAIL {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetRailState__7JOBRAILi(struct JOBRAIL *pjob, int st);

// name: SafeHouse port (JOBRAIL::Enter)
void Enter__7JOBRAIL(struct JOBRAIL *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetRailState__7JOBRAILi(pjob, 0);
}
