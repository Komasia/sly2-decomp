/* func_001626C0: add an object shown in a job state (at most 32). */
#include "h2_task.h"
int func_00161FC8(int nState);
void func_001626C0(JOB *pjob, int oid, int nState, int oidOwner, int iwrec)
{
    if (pjob->fDisabled == 0 && pjob->cobje < 32) {
        TASKOBJE *pobje = &pjob->aobje[pjob->cobje++];
        pobje->oid = oid;
        pobje->oidOwner = oidOwner;
        pobje->grfState = func_00161FC8(nState);
        pobje->iwrec = iwrec;
    }
}
