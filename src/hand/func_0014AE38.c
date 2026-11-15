/* JOBCHASE::SetState (job 0xB6, Carmelita's chase): ends the old state (the aim reset, the constraints back on,
 * the action's cooldown), ends the child job, then starts the new one: 0 decide (held still facing the player),
 * 1 run to the next graph entry (0xA7 along the guard's own path), 2 hop to it (0xAC), 3 the action on the target
 * (0xA4), 4 held still (0x9E). Layouts: SafeHouse port (aichase.h, aijobs.h, aipursuit.h, guard.h). */
#include "so.h"
extern qword D_002A2DD0;   /* the zero vector */
extern char g_sw[];
#include "clock.h"

/* the guard's root-motion velocity (+0x190), three words cleared */
struct VEL3 { int x; int y; int z; };
/* ACTIONOBJ (cid 0x78): an action the guard can take */
struct ACTIONOBJ { char pad[0x60]; float tWaitMin; float tWaitMax; };   /* +0x60: the wait after it (355) */
/* the guard's own path object (+0x294: a PATH), its curve's points */
struct PATHLO { char pad[0xE8]; int cpos; char pad2[0xF4 - 0xEC]; qword *apos; };
/* GUARD fragment */
struct GUARD {
    int pad[3]; VTENT *vt; char pad1[0x190 - 0x10]; struct VEL3 vecVel; char pad2[0x294 - 0x19C];
    struct PATHLO *ppath; char pad3[0x38C - 0x298]; void *ploTarget; char pad4[0xF04 - 0x390];
    float tNextAction;     /* +0xF04: the next action's time (the selector's cooldown) */
};
/* JOBCHASE (0xB6, 0x50 bytes); field: SafeHouse port */
struct JOBCHASE {
    char pad[0x10];
    struct GUARD *pguard;           /* AIJOB +0x10 */
    char pad1[4];
    char pchild[0x18];              /* AIJOB +0x18: the child job (passed by address) */
    int st;                         /* +0x30 */
    float tSt;                      /* +0x34 */
    char pad2[0x44 - 0x38];         /* +0x38 pgraph, +0x3C i, +0x40 iTarget */
    struct ACTIONOBJ *paction;      /* +0x44 */
};
/* the child jobs pushed (func_00205438(pguard, cid)) */
struct JOBMOVE9E { int pad[3]; VTENT *vt; char pad1[0x38 - 0x10]; void *ploFace; int nAnim; };
struct JOBFOLLOW { int pad[3]; VTENT *vt; char pad1[0x40 - 0x10]; int fNoAvoid; char pad2[0x64 - 0x44]; float sArrive;
                   char pad3[0xC0 - 0x68]; int kMove; char pad4[4]; void *ploArg; };
struct JOBUSE { int pad[3]; VTENT *vt; char padx[0x50 - 0x10]; qword pos; char pad1[0x68 - 0x60]; int nExtra; };
struct JOBACT { int pad[3]; VTENT *vt; char pad1[0x30 - 0x10]; void *ptarget; char pad2[8]; struct ACTIONOBJ *paction; };
void SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *, int, int, qword);
void SetAloCnstrLin__FP3ALOi(struct GUARD *, int);
void SetAloCnstrAng__FP3ALOi(struct GUARD *, int);
float GRandInRange__Fff(float, float);
void EndChildJob__FPP5AIJOB(void *);
void *func_00205438(struct GUARD *, int);   /* push a child job of the class */
void *PloPlayerPo__FP2SW(void *);
qword PosOfLo__FP2LO(void *);
void *PloEntry__8JOBCHASE(struct JOBCHASE *);
void RecalcCrv__FP3CRV(struct PATHLO *);
void Follow__9JOBFOLLOWP3CRVi(struct JOBFOLLOW *, struct PATHLO *, int);

#define VCALL0(po, n) { VTENT *e = &(po)->vt[n]; ((void (*)(void *))e->pfn)(VT_THIS((po), e)); }
#define AIJOB_Enter 8          /* vt slot */
#define ALO_SetVelocityTo 35   /* vt slot */
#define ALO_SetAngVelocityTo 36

// name: SafeHouse port (JOBCHASE::SetState)
void SetState__8JOBCHASEi(struct JOBCHASE *pjob, int state)
{
    if (state == pjob->st)
        return;
    switch (pjob->st) {
    case 0:
        SetGuardActionAim__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(pjob->pguard, 0, 0, D_002A2DD0);
        break;
    case -1:
    case 1:
        SetAloCnstrLin__FP3ALOi(pjob->pguard, 1);
        SetAloCnstrAng__FP3ALOi(pjob->pguard, 1);
        break;
    case 3: {
        float t = g_clock.t;
        pjob->pguard->tNextAction = t + GRandInRange__Fff(pjob->paction->tWaitMin, pjob->paction->tWaitMax);
        pjob->paction = 0;
        break;
    }
    }
    EndChildJob__FPP5AIJOB(pjob->pchild);
    pjob->st = state;
    pjob->tSt = g_clock.t;
    switch (state) {
    case 0: {
        struct JOBMOVE9E *pjobMove = func_00205438(pjob->pguard, 0x9E);
        pjobMove->ploFace = PloPlayerPo__FP2SW(g_sw);
        VCALL0(pjobMove, AIJOB_Enter);
        {
            struct GUARD *pguard = pjob->pguard;
            VTENT *e = &pguard->vt[ALO_SetVelocityTo];
            ((void (*)(void *, qword))e->pfn)(VT_THIS(pguard, e), D_002A2DD0);
        }
        {
            struct GUARD *pguard = pjob->pguard;
            VTENT *e = &pguard->vt[ALO_SetAngVelocityTo];
            ((void (*)(void *, qword))e->pfn)(VT_THIS(pguard, e), D_002A2DD0);
        }
        {
            struct VEL3 *pvel = &pjob->pguard->vecVel;
            pvel->x = pvel->y = pvel->z = 0;
        }
        break;
    }
    case 1: {
        struct PATHLO *ppath = pjob->pguard->ppath;
        struct JOBFOLLOW *pjobFollow;
        ppath->cpos = 2;
        {
            qword *apos = ppath->apos;
            *apos = PosOfLo__FP2LO(pjob->pguard);
            apos = ppath->apos;
            apos[1] = PosOfLo__FP2LO(PloEntry__8JOBCHASE(pjob));
        }
        RecalcCrv__FP3CRV(ppath);
        pjobFollow = func_00205438(pjob->pguard, 0xA7);
        Follow__9JOBFOLLOWP3CRVi(pjobFollow, ppath, 0);
        pjobFollow->kMove = 8;
        pjobFollow->fNoAvoid = 1;
        pjobFollow->sArrive = 25.0f;
        pjobFollow->ploArg = PloPlayerPo__FP2SW(g_sw);
        VCALL0(pjobFollow, AIJOB_Enter);
        pjob->pguard->tNextAction = g_clock.t;
        SetAloCnstrLin__FP3ALOi(pjob->pguard, 0);
        SetAloCnstrAng__FP3ALOi(pjob->pguard, 0);
        break;
    }
    case 2: {
        struct JOBUSE *pjobUse = func_00205438(pjob->pguard, 0xAC);
        pjobUse->pos = PosOfLo__FP2LO(PloEntry__8JOBCHASE(pjob));
        pjobUse->nExtra = 1;
        VCALL0(pjobUse, AIJOB_Enter);
        break;
    }
    case 3: {
        struct JOBACT *pjobAct = func_00205438(pjob->pguard, 0xA4);
        pjobAct->ptarget = pjob->pguard->ploTarget;
        pjobAct->paction = pjob->paction;
        VCALL0(pjobAct, AIJOB_Enter);
        pjob->pguard->tNextAction = 3.40282346638528859812e+38f;
        break;
    }
    case 4: {
        struct JOBMOVE9E *pjobMove = func_00205438(pjob->pguard, 0x9E);
        pjobMove->ploFace = PloPlayerPo__FP2SW(g_sw);
        pjobMove->nAnim = 1;
        VCALL0(pjobMove, AIJOB_Enter);
        break;
    }
    case -1:
        SetAloCnstrLin__FP3ALOi(pjob->pguard, 0);
        SetAloCnstrAng__FP3ALOi(pjob->pguard, 0);
        break;
    }
}
