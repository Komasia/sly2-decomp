/* RestartJob: reset the job, make its first task available again, leave the current task if it is the job's,
 * broadcast event 0x1F (job restarted) and end the job if current. */
#include "h2_task.h"
extern TASK *D_003E0FA0;   /* the current task */
extern char g_game[];
void ResetJob__FP3JOB(JOB *pjob);
void ChangeTaskState__FP4TASKi(TASK *ptask, int nState);
void func_00163CE0(TASK *ptask);
void BroadcastTaskEvent__FP2SWiP2LO(void *pgame, int nEvent, JOB *pjob);
void func_00162908(JOB *pjob);
// name: SafeHouse port (RestartJob)
void RestartJob__FP3JOB(JOB *pjob)
{
    ResetJob__FP3JOB(pjob);
    ChangeTaskState__FP4TASKi(pjob->ptaskFirst, TASKS_Available);
    if (D_003E0FA0 && D_003E0FA0->pjob == pjob)
        func_00163CE0(D_003E0FA0);
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 0x1F, pjob);
    func_00162908(pjob);
}
