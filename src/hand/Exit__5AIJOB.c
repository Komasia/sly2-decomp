/* AIJOB::Exit (AIJOB vt slot 9, the base's): the job's child job is ended. */
#include "aijob.h"

void EndChildJob(AIJOB **ppjob) asm("EndChildJob__FPP5AIJOB");

// name: SafeHouse port (AIJOB::Exit)
void Exit__5AIJOB(AIJOB *pjob)
{
    EndChildJob(&pjob->pchild);
}
