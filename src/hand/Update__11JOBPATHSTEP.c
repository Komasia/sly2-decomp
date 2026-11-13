/* JOBPATHSTEP::Update (AIJOB vt slot 10): the base update; when the child goto job has arrived, the next step. */
#include "aijob.h"

void Update__5AIJOB(AIJOB *pjob);
int NArrived(AIJOB *pjobGoto) asm("NArrived__7JOBGOTO");
void Step(AIJOB *pjob, int n) asm("Step__11JOBPATHSTEPi");

// name: SafeHouse port (JOBPATHSTEP::Update)
void Update__11JOBPATHSTEP(AIJOB *pjob)
{
    Update__5AIJOB(pjob);
    if (NArrived(pjob->pchild))
        Step(pjob, 0);
}
