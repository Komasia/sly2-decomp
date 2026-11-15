/* FUN_001e53f8: add an event that closes the job (at most 32). */
#include "h2_task.h"
void FUN_001e53f8(JOB *pjob, int nEvent)
{
    if (pjob->cnEndClose < 32) {
        pjob->anEndClose[pjob->cnEndClose++] = nEvent;
    }
}
