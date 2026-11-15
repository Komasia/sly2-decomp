/* func_00162660: set the job's completion sequence: its screen object and the parts it plays. */
#include "h2_task.h"
void func_00162660(JOB *pjob, int oidScreen, int idPartComplete, int idPartNext)
{
    pjob->oidScreen = oidScreen;
    pjob->idPartComplete = idPartComplete;
    pjob->idPartNext = idPartNext;
}
