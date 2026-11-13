/* JOBCOMPANION::Enter (AIJOB vt slot 8): the base enter, then state 0. Layout: SafeHouse port (actorai.cpp). */
#include "aijob.h"

struct JOBCOMPANION {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetState__12JOBCOMPANIONi(struct JOBCOMPANION *pjob, int st);

// name: SafeHouse port (JOBCOMPANION::Enter)
void Enter__12JOBCOMPANION(struct JOBCOMPANION *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetState__12JOBCOMPANIONi(pjob, 0);
}
