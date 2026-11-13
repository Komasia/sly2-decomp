/* JOBLINK::Init (AIJOB vt slot 7): a guard crossing a link between navigation regions; st starts at -1 and the guard gets state 0x2C.
 * Layout: SafeHouse port (aijobs.h JOBLINK). */
#include "aijob.h"

struct GUARD;
struct NAVLINK;
struct JOBLINK {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct NAVLINK *plink;     /* field: SafeHouse port */
    /* 0x34 */ int irec;                  /* field: SafeHouse port - the record walked to */
    /* 0x38 */ int st;                    /* field: SafeHouse port */
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBLINK::Init)
void Init__7JOBLINK(struct JOBLINK *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = -1;
    AddGuardState(pjob->aijob.pguard, 0x2C);
}
