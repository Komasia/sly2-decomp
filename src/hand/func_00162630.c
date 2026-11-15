/* func_00162630: add an event that ends the job (at most 32). */
#include "h2_task.h"
void func_00162630(JOB *pjob, int nEvent)
{
    if (pjob->cnEnd < 32) {
        pjob->anEnd[pjob->cnEnd++] = nEvent;
    }
}
