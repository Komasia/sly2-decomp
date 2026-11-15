/* JOBRAIL::Init (0xB8): no state, full speed, the guard's state 0x1B added. */
#include "h2_aijobs.h"

void Init__5AIJOB(JOBRAIL *pjob);
void AddGuardState__FP5GUARDi(struct GUARD *pguard, int gs);

// name: SafeHouse port (JOBRAIL::Init)
void Init__7JOBRAIL(JOBRAIL *pjob)
{
    Init__5AIJOB(pjob);
    pjob->st = -1;
    pjob->uSpeed = 1.0f;
    AddGuardState__FP5GUARDi(pjob->aijob.pguard, 0x1B);
}
