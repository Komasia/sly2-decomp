/* JOBSLEEP::Init (AIJOB vt slot 7): asleep (Bentley's dart) - a move (JOBMOVE) of animation state index 0x10, its own state
 * stSleep none (-1). Layout: SafeHouse port (aijobs.h JOBSLEEP). */
#include "aijob.h"

struct JOBSLEEP {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ int stSleep;   /* field: SafeHouse port */
};
void InitJobmove(JOBMOVE *pjob) asm("Init__7JOBMOVE");

// name: SafeHouse port (JOBSLEEP::Init)
void Init__8JOBSLEEP(struct JOBSLEEP *pjob)
{
    InitJobmove(&pjob->jobmove);
    pjob->jobmove.nAnim = 0x10;
    pjob->stSleep = -1;
}
