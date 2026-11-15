/* JOBB2::Enter (AIJOB vt slot 8): the base enter, then standing. */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void SetB2State(JOBB2 *pjob, int st) asm("SetB2State__5JOBB2i");

// name: SafeHouse port (JOBB2::Enter)
void Enter__5JOBB2(JOBB2 *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetB2State(pjob, B2S_Stand);
}
