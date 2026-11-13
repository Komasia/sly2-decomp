/* JOBB4::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct LO;
struct JOBB4 {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetB4State(struct JOBB4 *pjob, int n) asm("SetB4State__5JOBB4i");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");
void SetGuardPursued(struct GUARD *pguard, struct LO *plo) asm("SetGuardPursued__FP5GUARDP2LO");

// name: SafeHouse port (JOBB4::Exit)
void Exit__5JOBB4(struct JOBB4 *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetB4State(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x22);
    SetGuardPursued(pjob->aijob.pguard, 0);
}
