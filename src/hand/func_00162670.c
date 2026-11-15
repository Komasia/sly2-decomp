/* func_00162670: whether the job applies its state changes: not disabled, not in change mode 2 / 3, and the world
 * not in its func_0020E040 state. */
#include "h2_task.h"
extern char g_sw[];
int func_0020E040(void *psw);
int func_00162670(JOB *pjob)
{
    if (pjob->fDisabled == 0 && pjob->nMode != 2 && pjob->nMode != 3)
        return func_0020E040(g_sw) == 0;
    return 0;
}
