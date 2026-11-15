/* JOBB1::Exit (AIJOB vt slot 9): no launch state, then the move ends. */
#include "h2_aijobs.h"

void SetState(JOBB1 *pjob, int st) asm("SetState__5JOBB1i");
void Exit__7JOBMOVE(JOBMOVE *pjob);

// name: SafeHouse port (JOBB1::Exit)
void Exit__5JOBB1(JOBB1 *pjob)
{
    SetState(pjob, LAUNCHS_None);
    Exit__7JOBMOVE(&pjob->jobmove);
}
