/* JOBGOTO::NArrived: in its state 1, whether the follow child job has arrived (then 1); else 0.
 * Layout: SafeHouse port (aijobs.h JOBGOTO). */
#include "aijob.h"

struct JOBGOTO {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;     /* field: SafeHouse port */
};
int FArrived__9JOBFOLLOW(AIJOB *pjob);

// name: SafeHouse port (JOBGOTO::NArrived)
int NArrived__7JOBGOTO(struct JOBGOTO *pjob)
{
    int st = pjob->st;
    int n = 0;
    if (st == 1)
        n = FArrived__9JOBFOLLOW(pjob->aijob.pchild) ? st : 0;
    return n;
}
