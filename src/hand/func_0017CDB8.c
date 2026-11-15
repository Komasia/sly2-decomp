/* JOBRAIL::SetDirection: the goal is the rail's end (forward) or its start; the guard's direction set from it, then
 * moving. */
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
void SetRailState__7JOBRAILi(JOBRAIL *pjob, int st);

// name: SafeHouse port (JOBRAIL::SetDirection)
void SetDirection__7JOBRAILi(JOBRAIL *pjob, int fForward)
{
    struct CRV *pcrv = pjob->aijob.pguard->pcrvMove;
    if (fForward) pjob->sGoal = SMaxCrv__FP3CRV(pcrv); else pjob->sGoal = SMinCrv__FP3CRV(pcrv);
    pjob->aijob.pguard->fForward = pjob->aijob.pguard->sMove < pjob->sGoal;
    SetRailState__7JOBRAILi(pjob, 0);
}
