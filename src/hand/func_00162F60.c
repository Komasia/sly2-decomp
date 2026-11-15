/* JobCompleteClose: a job is completed: its last task closed (unless fNoClose), event 0x20 (job completed)
 * broadcast, the job ended if current, and the game auto-saved (unless fNoClose). */
#include "h2_task.h"
extern char g_game[];
extern char D_002E65E0[];   /* g_save */
void ChangeTaskState__FP4TASKi(TASK *ptask, int nState);
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int nEvent, JOB *pjob);
void func_00162908(JOB *pjob);
void HudAutoSave(void *psave, int n) asm("HudAutoSave__FP4SAVEi");
// name: SafeHouse port (JobCompleteClose)
void JobCompleteClose__FP3JOB(JOB *pjob)
{
    if (!pjob->fNoClose)
        ChangeTaskState__FP4TASKi(pjob->ptaskLast, TASKS_Closed);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x20, pjob);
    func_00162908(pjob);
    if (!pjob->fNoClose)
        HudAutoSave(D_002E65E0, 0);
}
