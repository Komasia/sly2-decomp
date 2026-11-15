/* JOBB0::Enter: grabbed; the guard's move along a navigation link, its response and its contacts dropped, the job
 * locks the guard, its detector cleared and the holder marked lost in it. */
#include "h2_aijobs.h"

struct DETECTOR;
extern qword D_002A2DD0;                /* a zero vector */
struct GUARD {
    /* 0x000 */ char pad0[0xF64];
    /* 0xf64 */ struct DETECTOR *pdet;  /* field: SafeHouse port */
};
void Enter__5AIJOB(JOBB0 *pjob);
void SetState__5JOBB0i(JOBB0 *pjob, int st);
void DetachGuardMove__FP5GUARD(struct GUARD *pguard);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, int paction, int n, qword vec);
void DetachAloContacts__FP3ALO(struct GUARD *pguard);
void LockJob__FP5AIJOB(JOBB0 *pjob);
void func_00153FF8(struct DETECTOR *pdet);
void func_00154038(struct DETECTOR *pdet, struct LO *plo, int st);

// name: SafeHouse port (JOBB0::Enter)
void Enter__5JOBB0(JOBB0 *pjob)
{
    Enter__5AIJOB(pjob);
    SetState__5JOBB0i(pjob, HELDS_Grabbed);
    DetachGuardMove__FP5GUARD(pjob->aijob.pguard);
    SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(pjob->aijob.pguard, 0, 0, D_002A2DD0);
    DetachAloContacts__FP3ALO(pjob->aijob.pguard);
    LockJob__FP5AIJOB(pjob);
    func_00153FF8(pjob->aijob.pguard->pdet);
    if (pjob->ploHolder) func_00154038(pjob->aijob.pguard->pdet, pjob->ploHolder, 2);
}
