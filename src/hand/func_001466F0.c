/* class: JOBCOMPANIONATTACK, Sly's (cid 0xC5) attack job, Enter (AIJOB vt slot 8): the base enter, state 0, the enemy made the
 * actor's targets (vt slot 95, SafeHouse SetActorTargets(pactor, 4, ploEnemy, 4, ploEnemy)) and the actor's
 * attacking flag (+0x10E0 bit 0) set. Layout: SafeHouse port (actorai.h JOBCOMPANIONATTACK). */
#include "vtbl.h"
struct ACTOR {
    /* 0x0000 */ char pad0[0xC];
    /* 0x000c */ VTENT *vt;
    /* 0x0010 */ char pad10[0x10E0 - 0x10];
    /* 0x10e0 */ int grf10E0;   /* field: SafeHouse port - bit 0: attacking */
};
struct JOBCOMPANIONATTACK {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct ACTOR *pactor;   /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad14[0x38 - 0x14];
    /* 0x38 */ int ploEnemy;           /* field: SafeHouse port */
};
#define VTS_SetActorTargets 95
#define ACTORF_Attacking 1
void Enter__5AIJOB(struct JOBCOMPANIONATTACK *pjob);
void SetState__12JOBSLYATTACKi(struct JOBCOMPANIONATTACK *pjob, int st);
void func_001466F0(struct JOBCOMPANIONATTACK *pjob)
{
    struct ACTOR *pactor;
    VTENT *pvte;
    Enter__5AIJOB(pjob);
    SetState__12JOBSLYATTACKi(pjob, 0);
    pactor = pjob->pactor;
    pvte = &pactor->vt[VTS_SetActorTargets];
    ((void (*)(void *, int, int, int, int))pvte->pfn)(VT_THIS(pactor, pvte), 4, pjob->ploEnemy, 4, pjob->ploEnemy);
    pjob->pactor->grf10E0 |= ACTORF_Attacking;
}
