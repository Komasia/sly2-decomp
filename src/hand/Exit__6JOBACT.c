/* JOBACT::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBACT {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetActState(struct JOBACT *pjob, int n) asm("SetActState__6JOBACTi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBACT::Exit)
void Exit__6JOBACT(struct JOBACT *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetActState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x18);
}
