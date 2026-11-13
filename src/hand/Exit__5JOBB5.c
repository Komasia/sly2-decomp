/* JOBB5::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBB5 {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetB5State(struct JOBB5 *pjob, int n) asm("SetB5State__5JOBB5i");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBB5::Exit)
void Exit__5JOBB5(struct JOBB5 *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetB5State(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x23);
}
