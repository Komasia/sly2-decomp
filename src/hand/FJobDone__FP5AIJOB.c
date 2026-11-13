/* FJobDone: a job above this one holds the actor (the hold count +0x20). Layout: SafeHouse port (ai.h AIJOB). */
#include "aijob.h"

// name: SafeHouse port (FJobDone, ai.h)
int FJobDone__FP5AIJOB(AIJOB *pjob)
{
    return pjob->cLock > 0;
}
