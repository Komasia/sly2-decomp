/* func_00164098: the state-machine goal standing for a task's state (0x612..0x615; -1 for none). */
#include "h2_task.h"
int func_00164098(TASK *ptask)
{
    switch (ptask->nState) {
    case TASKS_Locked: return 0x612;
    case TASKS_Available: return 0x613;
    case TASKS_Done: return 0x614;
    case TASKS_Closed: return 0x615;
    }
    return -1;
}
