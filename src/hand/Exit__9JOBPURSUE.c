/* JOBPURSUE::Exit (AIJOB subclass method, AIJOB vt slot 9). */
#include "aijob.h"

struct GUARD;
struct JOBPURSUE {
    /* 0x00 */ AIJOB aijob;
};
void Exit__5AIJOB(AIJOB *pjob);
void SetPursueState(struct JOBPURSUE *pjob, int n) asm("SetPursueState__9JOBPURSUEi");
void RemoveGuardState(struct GUARD *pguard, int gs) asm("RemoveGuardState__FP5GUARDi");

// name: SafeHouse port (JOBPURSUE::Exit)
void Exit__9JOBPURSUE(struct JOBPURSUE *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetPursueState(pjob, -1);
    RemoveGuardState(pjob->aijob.pguard, 0x1D);
}
