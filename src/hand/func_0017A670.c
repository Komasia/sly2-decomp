/* JOBSLEEP::Update: the move goes on; asleep until the wake time, then waking; the guard's held noise follows it. */
#include "clock.h"
#include "h2_aijobs.h"

struct NOISE { char pad0[0x20]; qword pos; };
struct GUARD {
    /* 0x000 */ char pad0[0x35C];
    /* 0x35c */ struct NOISE *pnoise;   /* field: SafeHouse port - the guard's held noise */
};
void Update__7JOBMOVE(JOBSLEEP *pjob);
void SetSleepState__8JOBSLEEPi(JOBSLEEP *pjob, int st);
qword PosOfLo__FP2LO(struct GUARD *pguard);

// name: SafeHouse port (JOBSLEEP::Update)
void Update__8JOBSLEEP(JOBSLEEP *pjob)
{
    int st;
    Update__7JOBMOVE(pjob);
    do {
        st = pjob->stSleep;
        if (st == SLEEPS_Asleep && g_clock.t > pjob->tWake) SetSleepState__8JOBSLEEPi(pjob, SLEEPS_Waking);
    } while (pjob->stSleep != st);
    { struct GUARD *pguard = pjob->jobmove.aijob.pguard; struct NOISE *pnoise = pguard->pnoise; pnoise->pos = PosOfLo__FP2LO(pguard); }
}
