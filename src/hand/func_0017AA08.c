/* JOBB1::Enter: the move starts, the guard's response cleared, its navigation-link move dropped, the launch starts
 * (rising), the job locks the guard and the launching owner is marked lost in the detector. */
#include "h2_aijobs.h"

struct DETECTOR;
extern qword D_002A2DD0;                /* a zero vector */
struct GUARD {
    /* 0x000 */ char pad0[0xF64];
    /* 0xf64 */ struct DETECTOR *pdet;  /* field: SafeHouse port */
};
void Enter__7JOBMOVE(JOBB1 *pjob);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, int paction, int n, qword vec);
void DetachGuardMove__FP5GUARD(struct GUARD *pguard);
void SetState__5JOBB1i(JOBB1 *pjob, int st);
void LockJob__FP5AIJOB(JOBB1 *pjob);
void func_00154038(struct DETECTOR *pdet, struct LO *plo, int st);

// name: SafeHouse port (JOBB1::Enter)
void Enter__5JOBB1(JOBB1 *pjob)
{
    Enter__7JOBMOVE(pjob);
    SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(pjob->jobmove.aijob.pguard, 0, 0, D_002A2DD0);
    DetachGuardMove__FP5GUARD(pjob->jobmove.aijob.pguard);
    SetState__5JOBB1i(pjob, LAUNCHS_Rise);
    LockJob__FP5AIJOB(pjob);
    func_00154038(pjob->jobmove.aijob.pguard->pdet, pjob->ploOwner, 2);
}
