/* JOBUSE::Exit (AIJOB vt slot 9): the move ends and the job lets go of the guard. */
#include "h2_aijobs.h"

void Exit__7JOBMOVE(JOBMOVE *pjob);
void UnlockJob(AIJOB *pjob) asm("UnlockJob__FP5AIJOB");

// name: SafeHouse port (JOBUSE::Exit)
void Exit__6JOBUSE(JOBUSE *pjob)
{
    Exit__7JOBMOVE(&pjob->jobmove);
    UnlockJob(&pjob->jobmove.aijob);
}
