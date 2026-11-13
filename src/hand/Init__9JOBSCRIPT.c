/* JOBSCRIPT::Init (AIJOB vt slot 7): the base init, and the guard gets state 0x21 (running a command list).
 * Layout: SafeHouse port (aijobs.h JOBSCRIPT). */
#include "aijob.h"

void Init__5AIJOB(AIJOB *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBSCRIPT::Init, aijobs.cpp)
void Init__9JOBSCRIPT(AIJOB *pjob)
{
    Init__5AIJOB(pjob);
    AddGuardState__FP5GUARDi(pjob->pguard, 0x21);
}
