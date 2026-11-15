/* JOBBD::Exit: the base exit, no state, the guard's detector reset, nothing pursued and its state 0x2B gone. */
#include "h2_aijobs.h"

struct DETECTOR;
struct GUARD {
    /* 0x000 */ char pad0[0xF64];
    /* 0xf64 */ struct DETECTOR *pdet;  /* field: SafeHouse port */
};
void Exit__5AIJOB(JOBBD *pjob);
void SetState__5JOBBDi(JOBBD *pjob, int st);
void func_00153FF8(struct DETECTOR *pdet);
void SetGuardPursued__FP5GUARDP2LO(struct GUARD *pguard, int plo);
void RemoveGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBBD::Exit)
void Exit__5JOBBD(JOBBD *pjob)
{
    Exit__5AIJOB(pjob);
    SetState__5JOBBDi(pjob, BDS_None);
    func_00153FF8(pjob->aijob.pguard->pdet);
    SetGuardPursued__FP5GUARDP2LO(pjob->aijob.pguard, 0);
    RemoveGuardState__FP5GUARDi(pjob->aijob.pguard, 0x2B);
}
