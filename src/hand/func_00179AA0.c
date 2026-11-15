/* JOBWAIT::Enter: the guard's patrol (or, for a guard that walks home, its home list; neither: idle), its saved place
 * re-found nearest the guard, then the patrol (or held, when the guard is held still). */
#include "h2_aijobs.h"
#include "h2_cmdlist.h"

struct GUARD {
    /* 0x000 */ char pad0[0x2DC];
    /* 0x2dc */ struct SAVEDSCRIPT saved;          /* field: SafeHouse port (saved2DC) */
    /* 0x2e8 */ struct CMDLIST *pcmdlistPatrol;    /* field: SafeHouse port */
    /* 0x2ec */ struct CMDLIST *pcmdlistHome;      /* field: SafeHouse port */
    /* 0x2f0 */ char pad2F0[0xFE8 - 0x2F0];
    /* 0xfe8 */ int grfFE8;                        /* field: SafeHouse port - 2: it walks (home) */
};
void Enter__5AIJOB(JOBWAIT *pjob);
void SetWaitState__7JOBWAITi(JOBWAIT *pjob, int st);
qword PosOfLo__FP2LO(struct GUARD *pguard);
void RefindSavedScript__FP7CMDLISTG9VU_VECTORP11SAVEDSCRIPT(struct CMDLIST *pcmdlist, qword pos, struct SAVEDSCRIPT *psaved);
int func_00209098(struct GUARD *pguard);   /* SafeHouse port: FGuardStill (0x209098) */

// name: SafeHouse port (JOBWAIT::Enter)
void Enter__7JOBWAIT(JOBWAIT *pjob)
{
    struct GUARD *pguard;
    Enter__5AIJOB(pjob);
    pguard = pjob->aijob.pguard;
    if (pguard->pcmdlistPatrol) pjob->pcmdlist = pguard->pcmdlistPatrol;
    else if (pguard->grfFE8 & 2) pjob->pcmdlist = pguard->pcmdlistHome;
    else { pjob->pcmdlist = 0; SetWaitState__7JOBWAITi(pjob, WAITS_Idle); return; }
    if (pjob->aijob.pguard->saved.pcmd)
        RefindSavedScript__FP7CMDLISTG9VU_VECTORP11SAVEDSCRIPT(pjob->pcmdlist, PosOfLo__FP2LO(pjob->aijob.pguard), &pjob->aijob.pguard->saved);
    if (func_00209098(pjob->aijob.pguard)) SetWaitState__7JOBWAITi(pjob, WAITS_Held); else SetWaitState__7JOBWAITi(pjob, WAITS_Patrol);
}
