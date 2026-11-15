/* JOBWAIT: draw the patrol's pause time (once): now + a random time in the guard's patrol range (+0x2CC..+0x2D0;
 * FLT_MAX there: the patrol never pauses). SafeHouse port (aijobs.cpp JOBWAIT::SetWaitState, tA). */
#include "clock.h"
#include "h2_aijobs.h"

struct GUARD {
    /* 0x000 */ char pad0[0x2CC];
    /* 0x2cc */ float tPatrolMin;       /* field: SafeHouse port (tWaitA0) */
    /* 0x2d0 */ float tPatrolMax;       /* field: SafeHouse port (tWaitA1) */
};
float GRandInRange__Fff(float gMin, float gMax);

void func_00179E80(JOBWAIT *pjob)
{
    if (pjob->tPause < 3.40282346638528859812e+38f) return;
    if (pjob->aijob.pguard->tPatrolMin == 3.40282346638528859812e+38f) pjob->tPause = 3.40282346638528859812e+38f;
    else { float t = g_clock.t; pjob->tPause = t + GRandInRange__Fff(pjob->aijob.pguard->tPatrolMin, pjob->aijob.pguard->tPatrolMax); }
}
