/* func_00162660: set the job's +0xAC..+0xB4 (the first: an object's oid, found at StartJob). */
#include "h2_task.h"
void func_00162660(JOB *pjob, int oidAC, int nB0, int nB4)
{
    pjob->oidAC = oidAC;
    pjob->nB0 = nB0;
    pjob->nB4 = nB4;
}
