/* JOBB0::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBB0 {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetState(struct JOBB0 *pjob, int n) asm("SetState__5JOBB0i");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBB0::Exit)
void Exit__5JOBB0(struct JOBB0 *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x16);
}
