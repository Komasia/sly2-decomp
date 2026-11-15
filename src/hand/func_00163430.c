/* NJobOpen: how far a job is open: its first task's state until that is done, then its last task's (at least 1). */
#include "h2_task.h"
static inline int Max(int a, int b) { return a > b ? a : b; }
// name: SafeHouse port (NJobOpen)
int NJobOpen__FP3JOB(JOB *pjob)
{
    int nState = pjob->ptaskFirst->nState;
    return nState < 2 ? nState : Max(pjob->ptaskLast->nState, 1);
}
