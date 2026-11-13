/* JOBB2::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBB2 {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetB2State(struct JOBB2 *pjob, int n) asm("SetB2State__5JOBB2i");

// name: SafeHouse port (JOBB2::Enter)
void Enter__5JOBB2(struct JOBB2 *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetB2State(pjob, 0);
}
