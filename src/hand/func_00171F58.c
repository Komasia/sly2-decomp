/* JOBINVESTIGATE::Init: the base init, the guard's state 0x1F (investigating), no state, no deadlines. */
#include "h2_aijobs.h"
void Init__5AIJOB(JOBINVESTIGATE *pjob);
void AddGuardState__FP5GUARDi(void *pguard, int gs);
// name: SafeHouse port (JOBINVESTIGATE::Init)
void Init__14JOBINVESTIGATE(JOBINVESTIGATE *pjob) { Init__5AIJOB(pjob); AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x1F); pjob->st = -1; pjob->t40 = pjob->tEnd = 3.40282346638528859812e+38f; }
