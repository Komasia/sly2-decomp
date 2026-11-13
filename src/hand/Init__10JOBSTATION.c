/* JOBSTATION::Init (AIJOB vt slot 7): a guard keeping to a station object; st starts at -1 and the guard gets state 0x26.
 * Layout: SafeHouse port (aijobs.h JOBSTATION). */
#include "aijob.h"

struct GUARD;
struct LO;
struct JOBSTATION {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct LO *plo;           /* field: SafeHouse port - the station object */
    /* 0x34 */ char pad34[0x50 - 0x34];
    /* 0x50 */ int st;                    /* field: SafeHouse port */
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBSTATION::Init)
void Init__10JOBSTATION(struct JOBSTATION *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->st = -1;
    AddGuardState(pjob->aijob.pguard, 0x26);
}
