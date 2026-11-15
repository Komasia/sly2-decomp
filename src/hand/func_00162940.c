/* ResetJob: clear the play counts of the job and of each of its tasks (each task then re-saved, func_001643B0; the
 * job by func_00163460). */
#include "h2_task.h"
void func_001643B0(TASK *ptask);
void func_00163460(JOB *pjob);
// name: SafeHouse port (ResetJob)
void ResetJob__FP3JOB(JOB *pjob)
{
    TASK *ptask;
    for (ptask = pjob->ptaskList; ptask; ptask = ptask->ptaskNextJob) {
        ptask->cPlayed = 0;
        func_001643B0(ptask);
    }
    pjob->cPlayed = 0;
    func_00163460(pjob);
}
