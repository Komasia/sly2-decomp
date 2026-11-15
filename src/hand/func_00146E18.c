/* JOBSLYATTACK::SetState: a new state; the strikes (2 cane, 3 jump, 4 dive) hold the job locked while they last.
 * Layout: SafeHouse port (actorai.h JOBCOMPANIONATTACK). */
#include "clock.h"
struct JOBSLYATTACK {
    /* 0x00 */ char pad[0x30];
    /* 0x30 */ int st;      /* field: SafeHouse port */
    /* 0x34 */ float tSt;   /* field: SafeHouse port */
};
void UnlockJob__FP5AIJOB(struct JOBSLYATTACK *pjob);
void LockJob__FP5AIJOB(struct JOBSLYATTACK *pjob);
// name: SafeHouse port (JOBSLYATTACK::SetState)
void SetState__12JOBSLYATTACKi(struct JOBSLYATTACK *pjob, int st)
{
    if (st == pjob->st) return;
    switch (pjob->st) {
    case 2: case 3: case 4:
        UnlockJob__FP5AIJOB(pjob);
    }
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case 2: case 3: case 4:
        LockJob__FP5AIJOB(pjob);
    }
}
