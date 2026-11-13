/* JOBLADDER::Init (AIJOB vt slot 7): a guard climbing the ladder / pipe it is attached to; st starts at -1 and the guard gets state 0x27.
 * Layout: SafeHouse port (aijobs.h JOBLADDER). */
#include "aijob.h"

struct GUARD;
struct JOBLADDER {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;                    /* field: SafeHouse port */
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLADDER::Init)
void Init__9JOBLADDER(struct JOBLADDER *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = -1;
    AddGuardState(pjob->aijob.pguard, 0x27);
}
