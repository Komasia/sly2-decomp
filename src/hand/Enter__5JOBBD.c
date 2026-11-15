/* JOBBD::Enter (AIJOB vt slot 8): the base enter, the alerted state, and the guard pursues the object kept away from.
 * Layout: SafeHouse port (aijobs.h). */
#include "h2_aijobs.h"

void Enter__5AIJOB(AIJOB *pjob);
void SetStateJobbd(JOBBD *pjob, int n) asm("SetState__5JOBBDi");
void SetGuardPursued(struct GUARD *pguard, struct LO *plo) asm("SetGuardPursued__FP5GUARDP2LO");

// name: SafeHouse port (JOBBD::Enter)
void Enter__5JOBBD(JOBBD *pjob)
{
    Enter__5AIJOB(&pjob->aijob);
    SetStateJobbd(pjob, BDS_Alerted);
    SetGuardPursued(pjob->aijob.pguard, pjob->ploFrom);
}
