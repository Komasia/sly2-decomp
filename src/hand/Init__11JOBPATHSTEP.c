/* JOBPATHSTEP::Init (AIJOB vt slot 7): a guard stepping along a path; s starts at -1.0f and the guard gets state 0x2E.
 * Layout: SafeHouse port (aijobs.h JOBPATHSTEP). */
#include "aijob.h"

struct GUARD;
struct CRV;
struct JOBPATHSTEP {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct CRV *pcrv;          /* field: SafeHouse port */
    /* 0x34 */ int fForward;              /* field: SafeHouse port */
    /* 0x38 */ float s;                   /* field: SafeHouse port - the distance along the path */
};
void Init__5AIJOB(AIJOB *pjob);
void AddGuardState(struct GUARD *pguard, int gs) asm("AddGuardState__FP5GUARDi");

// name: SafeHouse port (JOBPATHSTEP::Init)
void Init__11JOBPATHSTEP(struct JOBPATHSTEP *pjob)
{
    Init__5AIJOB(&pjob->aijob);
    pjob->s = -1.0f;
    AddGuardState(pjob->aijob.pguard, 0x2E);
}
