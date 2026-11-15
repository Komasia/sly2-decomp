/* JOBACTORWALK::Enter (AIJOB vt slot 8): the base enter, then a follow job (0xA8) pushed on the actor with the walk's
 * settings (no avoidance when running, the arrival distance, walking, the speed), the goal's path planned, and the
 * follow job entered. Layout: SafeHouse port (actorai.h JOBACTORWALK / JOBACTORFOLLOW). */
#include "vtbl.h"
#include "cid.h"
typedef int qword __attribute__((mode(TI)));
struct JOBACTORFOLLOW {
    /* 0x00 */ char pad0[0xC];
    /* 0x0c */ VTENT *pvt;
    /* 0x10 */ char pad10[0x40 - 0x10];
    /* 0x40 */ int fNoAvoid;        /* field: SafeHouse port (JOBFOLLOW) */
    /* 0x44 */ char pad44[0x64 - 0x44];
    /* 0x64 */ float sArrive;       /* field: SafeHouse port (JOBFOLLOW) */
    /* 0x68 */ char pad68[0xCC - 0x68];
    /* 0xcc */ int fWalk;           /* field: SafeHouse port */
    /* 0xd0 */ float uSpeedActor;   /* field: SafeHouse port */
};
struct JOBACTORWALK {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ void *pactor;        /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad14[0x30 - 0x14];
    /* 0x30 */ int fRun;            /* field: SafeHouse port */
    /* 0x34 */ float sArrive;       /* field: SafeHouse port */
    /* 0x38 */ int fWalk;           /* field: SafeHouse port */
    /* 0x3c */ float uSpeed;        /* field: SafeHouse port */
    /* 0x40 */ qword posGoal;       /* field: SafeHouse port */
};
#define VTS_AIJOB_Enter 8
void Enter__5AIJOB(void *pjob);
struct JOBACTORFOLLOW *func_00205438(void *pactor, int cid);   /* push a job of a class on the actor */
void SetGoal__12JOBACTORWALKG9VU_VECTOR(struct JOBACTORWALK *pjob, qword posGoal);
// name: SafeHouse port (JOBACTORWALK::Enter)
void Enter__12JOBACTORWALK(struct JOBACTORWALK *pjob)
{
    struct JOBACTORFOLLOW *pjobFollow;
    VTENT *pvte;
    Enter__5AIJOB(pjob);
    pjobFollow = func_00205438(pjob->pactor, CID_JOBACTORFOLLOW);
    pjobFollow->fNoAvoid = pjob->fRun;
    pjobFollow->sArrive = pjob->sArrive;
    pjobFollow->fWalk = pjob->fWalk;
    pjobFollow->uSpeedActor = pjob->uSpeed;
    SetGoal__12JOBACTORWALKG9VU_VECTOR(pjob, pjob->posGoal);
    pvte = &pjobFollow->pvt[VTS_AIJOB_Enter];
    ((void (*)(void *))pvte->pfn)(VT_THIS(pjobFollow, pvte));
}
