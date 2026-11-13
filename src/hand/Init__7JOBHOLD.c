/* JOBHOLD::Init (AIJOB subclass method, AIJOB vt slot 7). */
#include "aijob.h"

struct GUARD;
struct JOBHOLD {
    /* 0x00 */ AIJOB aijob;
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBHOLD::Init)
void Init__7JOBHOLD(struct JOBHOLD *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    AddGuardState(pjob->aijob.pguard, 0x28);
}
