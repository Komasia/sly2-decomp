/* JOBB2::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBB2 {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetB2State(struct JOBB2 *pjob, int n) asm("SetB2State__5JOBB2i");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBB2::Exit)
void Exit__5JOBB2(struct JOBB2 *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetB2State(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x20);
}
