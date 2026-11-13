/* JOBCOMPANION::Exit (AIJOB vt slot 9): the base exit, then state -1. Layout: SafeHouse port (actorai.cpp). */
#include "aijob.h"

struct JOBCOMPANION {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetState__12JOBCOMPANIONi(struct JOBCOMPANION *pjob, int st);

// name: SafeHouse port (JOBCOMPANION::Exit)
void Exit__12JOBCOMPANION(struct JOBCOMPANION *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetState__12JOBCOMPANIONi(pjob, -1);
}
