/* JOBGOTO::FStuck: on a path (states 1 / 2), whether the follow child is stuck (its state 3). */
#include "h2_aijobs.h"

int func_00178D80(AIJOB *pjobFollow);   /* JOBFOLLOW: stuck */

// name: SafeHouse port (JOBGOTO::FStuck)
int FStuck__7JOBGOTO(JOBGOTO *pjob)
{
    if (pjob->st >= GOTOS_Link) return 0;
    if (pjob->st <= GOTOS_Search) return 0;
    return func_00178D80(pjob->aijob.pchild);
}
