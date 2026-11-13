/* JOBACTORWALK::Init (AIJOB vt slot 7): a scripted walk goal: arrive within 40, walking, at full speed.
 * Layout: SafeHouse port (actorai.h JOBACTORWALK). */
#include "aijob.h"

struct JOBACTORWALK {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int fRun;        /* field: SafeHouse port */
    /* 0x34 */ float sArrive;   /* field: SafeHouse port */
    /* 0x38 */ int fWalk;       /* field: SafeHouse port */
    /* 0x3c */ float uSpeed;    /* field: SafeHouse port */
};
void Init__5AIJOB(AIJOB *pjob);

// name: SafeHouse port (JOBACTORWALK::Init)
void Init__12JOBACTORWALK(struct JOBACTORWALK *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->sArrive = 40.0f;
    pjob->fWalk = 1;
    pjob->uSpeed = 1.0f;
}
