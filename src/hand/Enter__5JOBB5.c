/* JOBB5::Enter (AIJOB subclass method, AIJOB vt slot 8). */
#include "aijob.h"

struct JOBB5 {
    /* 0x00 */ AIJOB aijob;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetB5State(struct JOBB5 *pjob, int n) asm("SetB5State__5JOBB5i");

// name: SafeHouse port (JOBB5::Enter)
void Enter__5JOBB5(struct JOBB5 *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetB5State(pjob, 0);
}
