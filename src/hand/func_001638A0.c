/* func_001638A0: add a state-machine goal for a task state (at most 32). */
#include "h2_task.h"
struct TASKV { char pad[0x50]; int fDisabled; char pad2[0xB0 - 0x54]; int csme; TASKSME *asme; };
void func_001638A0(struct TASKV *ptask, int nState, int oid, int oidSm, int oidGoal, int fNotInstant, int iwrec)
{
    if (ptask->fDisabled == 0 && ptask->csme < 32) {
        TASKSME *psme = &ptask->asme[ptask->csme++];
        psme->nState = nState; psme->oid = oid; psme->oidSm = oidSm; psme->oidGoal = oidGoal; psme->fNotInstant = fNotInstant; psme->iwrec = iwrec;
    }
}
