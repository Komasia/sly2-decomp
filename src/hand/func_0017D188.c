/* JOBLADDER::FDone: the guard is within 50 of the goal along the pipe. */
#include "h2_aijobs.h"
struct GUARD { char pad0[0xF88]; float sMove; };   /* sMove: field: SafeHouse port */
int func_0017D188(JOBLADDER *pjob) { return __builtin_fabsf(pjob->aijob.pguard->sMove - pjob->sGoal) < 50.0f; }
