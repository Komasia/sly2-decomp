/* JOBBD::Enter (AIJOB vt slot 8): the base enter, state 0, and the guard pursues the job's target (+0x38).
 * Layout: SafeHouse port (aijobs.h). */
#include "aijob.h"

struct LO;
struct JOBBD {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x38 - 0x24];
    /* 0x38 */ struct LO *ptarget;
};
void Enter__5AIJOB(AIJOB *pjob);
void SetStateJobbd(struct JOBBD *pjob, int n) asm("SetState__5JOBBDi");
void SetGuardPursued(struct GUARD *pguard, struct LO *plo) asm("SetGuardPursued__FP5GUARDP2LO");

// name: SafeHouse port (JOBBD::Enter)
void Enter__5JOBBD(struct JOBBD *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetStateJobbd(pjob, 0);
    SetGuardPursued(pjob->aijob.pguard, pjob->ptarget);
}
