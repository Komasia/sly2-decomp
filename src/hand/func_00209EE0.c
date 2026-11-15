#include "stepguard.h"
#include "vtbl.h"
extern float D_002C3DA8;   /* 800: the speed a released guard keeps at most */
/* the hold (0xB0) / carry (0xB1) jobs: the carry's launch state */
struct JOBB1 { char pad[0x50]; int stLaunch; };
int FGuardState(struct GUARD *pguard, int st) asm("FGuardState__FP5GUARDi");
struct JOBB1 *func_00205458(struct GUARD *pguard, int cid);
void SetState__5JOBB0i(struct JOBB1 *pjob, int st);
void SetState__5JOBB1i(struct JOBB1 *pjob, int st);
qword LimitVectorLength__FG9VU_VECTORf(qword vec, float sMax);
/* ReleaseGuardHeld (0x209EE0): the guard is let go: its hold job (states 0x12 / 0x13) or its carry job (state 0x17,
 * unless launching: 3 / 6) goes to state 2, and its velocity (vt slots 33 / 35) is limited to 800. */
// name: SafeHouse port (ReleaseGuardHeld)
void ReleaseGuardHeld__FP2LO(struct GUARD *pguard)
{
    if (FGuardState(pguard, 0x12) || FGuardState(pguard, 0x13)) {
        SetState__5JOBB0i(func_00205458(pguard, 0xB0), 2);
    } else {
        struct JOBB1 *pjob;
        if (!FGuardState(pguard, 0x17))
            return;
        pjob = func_00205458(pguard, 0xB1);
        if (pjob->stLaunch != 3 && pjob->stLaunch != 6)
            SetState__5JOBB1i(pjob, 2);
    }
    {
        qword vel = ((qword (*)(void *))pguard->step.po.so.lo.pvt[33].pfn)(VT_THIS(pguard, &pguard->step.po.so.lo.pvt[33]));
        vel = LimitVectorLength__FG9VU_VECTORf(vel, D_002C3DA8);
        ((void (*)(void *, qword))pguard->step.po.so.lo.pvt[35].pfn)(VT_THIS(pguard, &pguard->step.po.so.lo.pvt[35]), vel);
    }
}
