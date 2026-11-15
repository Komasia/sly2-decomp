/* JOBSHOOT::Init (0xAD): no shot state yet. */
#include "h2_aijobs.h"
void Init__5AIJOB(JOBSHOOT *pjob);
// name: SafeHouse port (JOBSHOOT::Init)
void Init__8JOBSHOOT(JOBSHOOT *pjob) { Init__5AIJOB(pjob); pjob->st = SHOOTS_None; }
