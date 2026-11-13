/* JOBMURRAYATTACK::SetState: the companion attack's state (Murray's AI); state 2 (the attack itself) holds the job
 * locked while it lasts. Layout: SafeHouse port (actorai.cpp JOBCOMPANIONATTACK). */
#include "aijob.h"
#include "clock.h"

struct JOBMURRAYATTACK {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ int st;      /* field: SafeHouse port */
    /* 0x34 */ float tSt;   /* field: SafeHouse port */
};
void LockJob__FP5AIJOB(AIJOB *pjob);
void UnlockJob__FP5AIJOB(AIJOB *pjob);

// name: SafeHouse port (JOBMURRAYATTACK::SetState)
void SetState__15JOBMURRAYATTACKi(struct JOBMURRAYATTACK *pjob, int st)
{
    int stOld = pjob->st;
    if (st != stOld) {
        if (stOld == 2)
            UnlockJob__FP5AIJOB(&pjob->aijob);
        pjob->st = st;
        pjob->tSt = g_clock.t;
        if (st == 2)
            LockJob__FP5AIJOB(&pjob->aijob);
    }
}
