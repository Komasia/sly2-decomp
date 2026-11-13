/* JOBPROX::Init (AIJOB vt slot 7): class 0x3C's command list run near Sly; st starts at -1 and the guard gets state 0x25.
 * Layout: SafeHouse port (aijobs.h JOBPROX). */
#include "aijob.h"

struct GUARD;
struct JOBPROX {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                    /* field: SafeHouse port */
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBPROX::Init)
void Init__7JOBPROX(struct JOBPROX *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = -1;
    AddGuardState(pjob->aijob.pguard, 0x25);
}
