struct JOBPURSUE { char pad[0x10]; void *pguard; char pad2[0x20]; int st; };
void Init__5AIJOB(struct JOBPURSUE *pjob);
void AddGuardState__FP5GUARDi(void *pjob, int n);
/* JOBPURSUE::Init: the base init, the guard's state 0x1D (pursuing), no pursuit state. */
// name: SafeHouse port (JOBPURSUE::Init)
void Init__9JOBPURSUE(struct JOBPURSUE *pjob) { Init__5AIJOB(pjob); AddGuardState__FP5GUARDi(pjob->pguard, 0x1D); pjob->st = -1; }
