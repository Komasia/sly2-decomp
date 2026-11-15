/* JOBGOTO::NArrived: on its path to the goal (state 1), whether the follow child job has arrived (then 1); else 0.
 * Layout: SafeHouse port (aijobs.h JOBGOTO). */
#include "h2_aijobs.h"

int FArrived__9JOBFOLLOW(AIJOB *pjob);

// name: SafeHouse port (JOBGOTO::NArrived)
int NArrived__7JOBGOTO(JOBGOTO *pjob)
{
    int st = pjob->st;
    int n = 0;
    if (st == GOTOS_Path)
        n = FArrived__9JOBFOLLOW(pjob->aijob.pchild) ? st : 0;
    return n;
}
