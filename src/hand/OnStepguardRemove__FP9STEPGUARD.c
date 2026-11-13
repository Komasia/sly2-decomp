/* OnStepguardRemove (the guards' vt slot 12): a guard taken out of the world: the SO's removal, then the pursued
 * object cleared, the job stack emptied and the +0x34C animation retracted. Layout: SafeHouse port (guard.h GUARD). */
struct LO;
struct ASEGA;
struct STEPGUARD {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char ajobs[0x34c - 0x26c];   /* the AI job stack (ClearJobs) */
    /* 0x34c */ struct ASEGA *pasega34C;     /* field: SafeHouse port */
};
void OnSoRemove__FP2SO(struct STEPGUARD *pguard);
void SetGuardPursued__FP5GUARDP2LO(struct STEPGUARD *pguard, struct LO *plo);
void ClearJobs__FP5ACTOR(void *pjobs);
void RetractAsegaPp__FPP5ASEGA(struct ASEGA **ppasega);

// name: SafeHouse port (OnRemoveGuard, guard.cpp: orig 0x2064D8)
void OnStepguardRemove__FP9STEPGUARD(struct STEPGUARD *pguard)
{
    OnSoRemove__FP2SO(pguard);
    SetGuardPursued__FP5GUARDP2LO(pguard, 0);
    ClearJobs__FP5ACTOR(pguard->ajobs);
    RetractAsegaPp__FPP5ASEGA(&pguard->pasega34C);
}
