/* JOBHOLD::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBHOLD {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBHOLD::Exit)
void Exit__7JOBHOLD(struct JOBHOLD *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    RemoveGuardState(pjob->aijob.pguard, 0x28);
}
