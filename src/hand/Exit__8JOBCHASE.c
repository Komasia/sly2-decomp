/* JOBCHASE::Exit (AIJOB vt slot 9): the chase ends: the base exit, state -1, the guard's state 0x24 removed, the
 * sound's alert mode count lowered (0x1FEEA0 on D_003DD040) and the guard's +0x4A4 set. Layout: SafeHouse port
 * (aichase.h JOBCHASE, guard.h GUARD). */
#include "aijob.h"

struct GUARD {
    /* 0x000 */ char pad0[0x4a4];
    /* 0x4a4 */ int f4A4;     /* field: SafeHouse port */
};
struct JOBCHASE {
    /* 0x00 */ AIJOB aijob;
};
extern char D_003DD040[];   /* SafeHouse: g_sound */
void Exit__5AIJOB(AIJOB *pjob);
void SetState__8JOBCHASEi(struct JOBCHASE *pjob, int st);
void RemoveGuardState__FP5GUARDi(struct GUARD *pguard, int gs);
void func_001FEEA0(void *psound);   /* SafeHouse: --fModeAlert */

// name: SafeHouse port (JOBCHASE::Exit)
void Exit__8JOBCHASE(struct JOBCHASE *pjob)
{
    Exit__5AIJOB(&pjob->aijob);
    SetState__8JOBCHASEi(pjob, -1);
    RemoveGuardState__FP5GUARDi(pjob->aijob.pguard, 0x24);
    func_001FEEA0(D_003DD040);
    pjob->aijob.pguard->f4A4 = 1;
}
