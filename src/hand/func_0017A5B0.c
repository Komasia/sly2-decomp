/* JOBSLEEP::SetSleepState: asleep: an SM entry gets the goal 0x44, the wake time is drawn from the guard's sleep range
 * (+0xE7C..+0xE80); waking: an SM entry gets the goal 0x43. */
#include "clock.h"
#include "h2_aijobs.h"

struct SMA;
struct KINDE { int k; void *pv; struct SMA *psma; int grf; };   /* field: SafeHouse port (guard.h KINDE) */
#define KINDK_Sm 1
struct GUARD {
    /* 0x000 */ char pad0[0xE7C];
    /* 0xe7c */ float tSleepMin;        /* field: SafeHouse port (gE7C) */
    /* 0xe80 */ float tSleepMax;        /* field: SafeHouse port (gE80) */
};
void SetSmaGoal__FP3SMA3OID(struct SMA *psma, int oidGoal);
float GRandInRange__Fff(float gMin, float gMax);

// name: SafeHouse port (JOBSLEEP::SetSleepState)
void SetSleepState__8JOBSLEEPi(JOBSLEEP *pjob, int st)
{
    if (st == pjob->stSleep) return;
    pjob->stSleep = st;
    pjob->gSt = st;
    switch (st) {
    case SLEEPS_Asleep:
        if (pjob->jobmove.pkinde->k == KINDK_Sm) SetSmaGoal__FP3SMA3OID(pjob->jobmove.pkinde->psma, 0x44);
        { float t = g_clock.t; pjob->tWake = t + GRandInRange__Fff(pjob->jobmove.aijob.pguard->tSleepMin, pjob->jobmove.aijob.pguard->tSleepMax); }
        break;
    case SLEEPS_Waking:
        if (pjob->jobmove.pkinde->k == st) SetSmaGoal__FP3SMA3OID(pjob->jobmove.pkinde->psma, 0x43);
        break;
    }
}
