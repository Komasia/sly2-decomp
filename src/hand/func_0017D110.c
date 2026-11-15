/* JOBLADDER::SetDirection: the goal is the pipe's end (forward) or its start; the guard's direction set from it, then
 * climbing. */
#include "h2_aijobs.h"

struct CRV;
struct GUARD {
    /* 0x000 */ char pad0[0xF84];
    /* 0xf84 */ struct CRV *pcrvMove;   /* field: SafeHouse port (ploMove) */
    /* 0xf88 */ float sMove;            /* field: SafeHouse port */
    /* 0xf8c */ int fForward;           /* field: SafeHouse port (nMoveKind) */
};
float SMaxCrv__FP3CRV(struct CRV *pcrv);
float SMinCrv__FP3CRV(struct CRV *pcrv);
void SetLadderState__9JOBLADDERi(JOBLADDER *pjob, int st);

// name: SafeHouse port (JOBLADDER::SetDirection)
void SetDirection__9JOBLADDERi(JOBLADDER *pjob, int fForward)
{
    struct CRV *pcrv = pjob->aijob.pguard->pcrvMove;
    if (fForward) pjob->sGoal = SMaxCrv__FP3CRV(pcrv); else pjob->sGoal = SMinCrv__FP3CRV(pcrv);
    pjob->aijob.pguard->fForward = pjob->aijob.pguard->sMove < pjob->sGoal;
    SetLadderState__9JOBLADDERi(pjob, 0);
}
