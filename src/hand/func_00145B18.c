#include "cid.h"
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
/* JOBCOMPANION::SetState: a new state, ending the child job. 0 following: a follow job (0xA8) pushed - copying the
 * followed player's controller (walk button only, after 0.1..0.3 s) when it is a PO - the path planned, the job
 * entered; 1 recovering to the point FNeedRecover found; 2 attacking: Murray / Bentley / Sly's attack job pushed on
 * the enemy and entered. Layout: SafeHouse port (actorai.h JOBCOMPANION / JOBACTORFOLLOW / JOBCOMPANIONATTACK). */
/* the job pushed: a JOBACTORFOLLOW (state 0) or a JOBCOMPANIONATTACK (state 2) */
struct JOBPUSHED {
    /* 0x00 */ char pad[0xC];
    /* 0x0c */ VTENT *vt;
    /* 0x10 */ char pad1[0x38 - 0x10];
    /* 0x38 */ int ploEnemy;    /* field: SafeHouse port (JOBCOMPANIONATTACK) */
    /* 0x3c */ char pad2[0xC0 - 0x3C];
    /* 0xc0 */ int pcCopy;      /* field: SafeHouse port (JOBACTORFOLLOW) - the followed player's controller */
    /* 0xc4 */ int grfCopy;     /* field: SafeHouse port */
    /* 0xc8 */ float dtCopy;    /* field: SafeHouse port */
};
struct PO { char pad[0x150]; int ppadctl; };   /* the player object's controller state */
struct JOBCOMPANION {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ void *pactor;            /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad1[4];
    /* 0x18 */ char pchild[0x30 - 0x18];   /* field: SafeHouse port (AIJOB) - the child job (its address is used) */
    /* 0x30 */ struct PO *ploFollow;    /* field: SafeHouse port */
    /* 0x34 */ char pad2[0x60 - 0x34];
    /* 0x60 */ int st;                  /* field: SafeHouse port */
    /* 0x64 */ float tSt;               /* field: SafeHouse port */
    /* 0x68 */ char pad3[0x80 - 0x68];
    /* 0x80 */ qword posRecover;        /* field: SafeHouse port */
    /* 0x90 */ int ploEnemy;            /* field: SafeHouse port */
};
#define PADBTN_Walk 0x08        /* the walk button: the only one copied */
#define VTS_AIJOB_Enter 8
#include "clock.h"
void EndChildJob__FPP5AIJOB(void *ppjobChild);
struct JOBPUSHED *func_00205438(void *pactor, int cid);   /* push a job of a class on the actor */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *plo, int cid);
float GRandInRange__Fff(float a, float b);
void PlanFollow__12JOBCOMPANION(struct JOBCOMPANION *pjob);
void RecoverTo__FP5ACTORG9VU_VECTOR(void *pactor, qword pos);
int func_00132EA0(void *plo);   /* the object's class id */
/* push an attack job of a class on the enemy, and enter it */
static __inline__ void Activate(struct JOBCOMPANION *pjob, int cid)
{
    struct JOBPUSHED *pjobAttack = func_00205438(pjob->pactor, cid);
    pjobAttack->ploEnemy = pjob->ploEnemy;
    ((void (*)(void *))pjobAttack->vt[VTS_AIJOB_Enter].pfn)(VT_THIS(pjobAttack, &pjobAttack->vt[VTS_AIJOB_Enter]));
}
// name: SafeHouse port (JOBCOMPANION::SetState)
void SetState__12JOBCOMPANIONi(struct JOBCOMPANION *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(pjob->pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case 0: {
        struct JOBPUSHED *pjobFollow = func_00205438(pjob->pactor, CID_JOBACTORFOLLOW);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->ploFollow, CID_PO)) {
            pjobFollow->pcCopy = pjob->ploFollow->ppadctl;
            pjobFollow->grfCopy = PADBTN_Walk;
            pjobFollow->dtCopy = GRandInRange__Fff(0.1f, 0.3f);
        }
        PlanFollow__12JOBCOMPANION(pjob);
        ((void (*)(void *))pjobFollow->vt[VTS_AIJOB_Enter].pfn)(VT_THIS(pjobFollow, &pjobFollow->vt[VTS_AIJOB_Enter]));
        break;
    }
    case 1:
        RecoverTo__FP5ACTORG9VU_VECTOR(pjob->pactor, pjob->posRecover);
        break;
    case 2:
        switch (func_00132EA0(pjob->pactor)) {
        case CID_MURRAY: Activate(pjob, CID_JOBMURRAYATTACK); break;
        case CID_BENTLEY: Activate(pjob, CID_JOBBENTLEYATTACK); break;
        case CID_JT: Activate(pjob, CID_JOBSLYATTACK); break;
        }
        break;
    }
}
