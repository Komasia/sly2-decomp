/* JOBRAIL::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBRAIL {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetRailState(struct JOBRAIL *pjob, int n) asm("SetRailState__7JOBRAILi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBRAIL::Exit)
void Exit__7JOBRAIL(struct JOBRAIL *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetRailState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x1B);
}
