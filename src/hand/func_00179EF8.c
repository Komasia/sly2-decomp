/* JOBWAIT: draw the pause's resume time (once): now + a random time in the guard's pause range (+0x2D4..+0x2D8;
 * FLT_MAX there: the pause never ends). SafeHouse port (aijobs.cpp JOBWAIT::SetWaitState, "orig 0x179EF8"). */
#include "clock.h"
#include "h2_aijobs.h"

struct GUARD {
    /* 0x000 */ char pad0[0x2D4];
    /* 0x2d4 */ float tPauseMin;        /* field: SafeHouse port (tWaitB0) */
    /* 0x2d8 */ float tPauseMax;        /* field: SafeHouse port (tWaitB1) */
};
float GRandInRange__Fff(float gMin, float gMax);

void func_00179EF8(JOBWAIT *pjob)
{
    if (pjob->tResume < 3.40282346638528859812e+38f) return;
    if (pjob->aijob.pguard->tPauseMin == 3.40282346638528859812e+38f) pjob->tResume = 3.40282346638528859812e+38f;
    else { float t = g_clock.t; pjob->tResume = t + GRandInRange__Fff(pjob->aijob.pguard->tPauseMin, pjob->aijob.pguard->tPauseMax); }
}
