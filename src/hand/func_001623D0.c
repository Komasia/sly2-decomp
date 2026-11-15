/* ApplyTaskSms: apply each state-machine goal of a list for a state (func_00162250). */
#include "h2_task.h"
void func_00162250(void *pv, TASKSME *psme, void *pvState, int nMode);
// name: SafeHouse port (ApplyTaskSms)
void ApplyTaskSms__FPvT0iT0i(void *pv, void *pvState, int csme, TASKSME *asme, int nMode)
{
    int i;
    for (i = 0; i < csme; i++)
        func_00162250(pv, &asme[i], pvState, nMode);
}
