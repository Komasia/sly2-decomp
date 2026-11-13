/* JOBPURSUE::Enter (AIJOB vt slot 8): the base enter, the pursuit's state 3, and the guard pursues the target.
 * Layout: SafeHouse port (aipursuit.h JOBPURSUE). */
#include "aijob.h"

struct LO;
struct JOBPURSUE {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct LO *ptarget;   /* field: SafeHouse port */
};
void Enter__5AIJOB(AIJOB *pjob);
void SetPursueState(struct JOBPURSUE *pjob, int n) asm("SetPursueState__9JOBPURSUEi");
void SetGuardPursued(struct GUARD *pguard, struct LO *plo) asm("SetGuardPursued__FP5GUARDP2LO");

// name: SafeHouse port (JOBPURSUE::Enter)
void Enter__9JOBPURSUE(struct JOBPURSUE *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetPursueState(pjob, 3);
    SetGuardPursued(pjob->aijob.pguard, pjob->ptarget);
}
