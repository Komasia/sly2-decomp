struct JOBACT { char pad[0x10]; void *pguard; char pad2[0x20]; int st; };
void Init__5AIJOB(struct JOBACT *pjob);
void AddGuardState__FP5GUARDi(void *pjob, int n);
/* JOBACT::Init: the base init, the guard's state 0x18 (acting), no action state. */
// name: SafeHouse port (JOBACT::Init)
void Init__6JOBACT(struct JOBACT *pjob) { Init__5AIJOB(pjob); AddGuardState__FP5GUARDi(pjob->pguard, 0x18); pjob->st = -1; }
