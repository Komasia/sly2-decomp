/* ResetJob: clear the play counts of the job and of each of its tasks (each task then re-saved, func_001643B0; the
 * job by func_00163460). */
#include "h2_task.h"
struct TASK { char pad[0x64]; int cPlayed; char pad2[0x84 - 0x68]; struct TASK *ptaskNext; };
void func_001643B0(struct TASK *ptask);
void func_00163460(JOB *pjob);
// name: SafeHouse port (ResetJob)
void ResetJob__FP3JOB(JOB *pjob)
{
    struct TASK *ptask;
    for (ptask = pjob->ptaskFirst; ptask; ptask = ptask->ptaskNext) {
        ptask->cPlayed = 0;
        func_001643B0(ptask);
    }
    pjob->cPlayed = 0;
    func_00163460(pjob);
}
