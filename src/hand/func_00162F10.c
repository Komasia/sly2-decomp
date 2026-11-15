/* func_00162F10 (SafeHouse: JobComplete): the job's last task is reached: with a screen object the completion
 * sequence starts (1), else the job is closed and the next one requested at once. */
#include "h2_task.h"
void SetJobSeq__FP3JOBi(JOB *pjob, int nSeq);
void JobCompleteClose__FP3JOB(JOB *pjob, int n);
void JobCompleteNext__FP3JOB(JOB *pjob);

void func_00162F10(JOB *pjob, int n)
{
    if (pjob->ploScreen != 0) {
        SetJobSeq__FP3JOBi(pjob, 1);
        return;
    }
    JobCompleteClose__FP3JOB(pjob, n);
    JobCompleteNext__FP3JOB(pjob);
}
