/* JOBSLEEP::Enter: the move starts asleep, the guard's detector is cleared and its held noise (the sleep's, SW +0x4024's
 * template 707) placed at the guard. */
#include "h2_aijobs.h"

struct SW;
struct DETECTOR;
struct NOISE;
extern struct SW g_sw;
struct GUARD {
    /* 0x000 */ char pad0[0x35C];
    /* 0x35c */ struct NOISE *pnoise;   /* field: SafeHouse port - the guard's held noise */
    /* 0x360 */ char pad360[0xF64 - 0x360];
    /* 0xf64 */ struct DETECTOR *pdet;  /* field: SafeHouse port */
};
void Enter__7JOBMOVE(JOBSLEEP *pjob);
void SetSleepState__8JOBSLEEPi(JOBSLEEP *pjob, int st);
void func_00153FF8(struct DETECTOR *pdet);
qword PosOfLo__FP2LO(struct GUARD *pguard);
void func_00156C80(struct SW *psw, int fOn, qword pos, struct GUARD *pguard, struct NOISE **ppnoise);

// name: SafeHouse port (JOBSLEEP::Enter)
void Enter__8JOBSLEEP(JOBSLEEP *pjob)
{
    Enter__7JOBMOVE(pjob);
    SetSleepState__8JOBSLEEPi(pjob, SLEEPS_Asleep);
    func_00153FF8(pjob->jobmove.aijob.pguard->pdet);
    func_00156C80(&g_sw, 1, PosOfLo__FP2LO(pjob->jobmove.aijob.pguard), pjob->jobmove.aijob.pguard, &pjob->jobmove.aijob.pguard->pnoise);
}
