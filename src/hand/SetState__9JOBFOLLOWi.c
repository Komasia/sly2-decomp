/* JOBFOLLOW::SetState (AIJOB vt slot 15; also JOBACTORFOLLOW's): a new state and its time.
 * Layout: SafeHouse port (aijobs.h JOBFOLLOW). */
#include "clock.h"

struct JOBFOLLOW {
    /* 0x00 */ char pad0[0x4c];
    /* 0x4c */ int st;      /* field: SafeHouse port */
    /* 0x50 */ float tSt;   /* field: SafeHouse port */
};

// name: SafeHouse port (JOBFOLLOW::SetState, aijobs.cpp)
void SetState__9JOBFOLLOWi(struct JOBFOLLOW *pjob, int st)
{
    if (st != pjob->st) {
        pjob->st = st;
        pjob->tSt = g_clock.t;
    }
}
