/* JOBNAVPOINT::Init (AIJOB subclass method, AIJOB vt slot 7). */
#include "aijob.h"

struct GUARD;
struct JOBNAVPOINT {
    /* 0x00 */ AIJOB aijob;
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBNAVPOINT::Init)
void Init__11JOBNAVPOINT(struct JOBNAVPOINT *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    AddGuardState(pjob->aijob.pguard, 0x2D);
}
