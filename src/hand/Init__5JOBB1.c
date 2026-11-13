/* JOBB1::Init (AIJOB vt slot 7): a launched guard, then the contextual strike's target - a move (JOBMOVE) of animation state index 0x17, its own state
 * stLaunch none (-1). Layout: SafeHouse port (aijobs.h JOBB1). */
#include "aijob.h"

struct JOBB1 {
    /* 0x00 */ JOBMOVE jobmove;
    /* 0x50 */ int stLaunch;   /* field: SafeHouse port */
};
void InitJobmove(JOBMOVE *pjob) asm("Init__7JOBMOVE");

// name: SafeHouse port (JOBB1::Init)
void Init__5JOBB1(struct JOBB1 *pjob)
{
    InitJobmove(&pjob->jobmove);
    pjob->jobmove.nAnim = 0x17;
    pjob->stLaunch = -1;
}
