/* func_00162728: add a state-machine goal for a job state (at most 32). */
#include "h2_task.h"
void func_00162728(JOB *pjob, int nState, int oid, int oidSm, int oidGoal, int iwrec)
{
    if (pjob->fDisabled == 0 && pjob->csme < 32) {
        TASKSME *psme = &pjob->asme[pjob->csme++];
        psme->iwrec = iwrec; psme->nState = nState; psme->oid = oid; psme->oidSm = oidSm; psme->oidGoal = oidGoal; psme->fNotInstant = 0;
    }
}
