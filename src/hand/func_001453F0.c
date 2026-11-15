// Match notes (Update__12JOBCOMPANION): `f = FNeedRecover__12JOBCOMPANION(p) != 0; if (f)` (stops loop.c hoisting constant 1), inline GClamp.
typedef int qword __attribute__((mode(TI)));
/* JOBCOMPANION::Update (AIJOB vt slot 10): the companion's state machine. 0 following: recover (1) when the followed
 * object is off the companion's navigation, attack (2) an enemy within 600 of either; 1 recovering until the jump
 * ends; 2 attacking (Murray / Bentley / Sly's attack job) until it is done, the enemy is out of 1200, or a recovery
 * is needed. While following, the follow job skips avoidance off the navigation, the path is planned again once the
 * followed object has moved 200, and the animation speed goes from svNear to svFar between sNear and sFar.
 * Layout: SafeHouse port (actorai.h JOBCOMPANION). */
struct LM { float gMin, gMax; };
struct GUARD;
struct REGENT { char pad[0x10]; void *preg; };   /* the actor's navigation region entry */
struct SOST { char pad[0xDC]; struct REGENT *pregent; };
struct ACTOR {
    /* 0x0000 */ char pad[0xE8];
    /* 0x00e8 */ struct SOST *psost;
    /* 0x00ec */ char pad2[0x2DC - 0xEC];
    /* 0x02dc */ int stJump;          /* jump.state: -1 when not jumping */
    /* 0x02e0 */ char pad3[0x1030 - 0x2E0];
    /* 0x1030 */ void *pasega;        /* field: SafeHouse port - the current animation */
};
struct JOBACTORFOLLOW { char pad[0x40]; int fNoAvoid; };
/* a companion's attack job (Murray / Bentley / Sly: JOBCOMPANIONATTACK) */
struct JOBCOMPANIONATTACK;
struct JOBCOMPANION {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct ACTOR *pactor;          /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad1[4];
    /* 0x18 */ struct JOBACTORFOLLOW *pchild; /* field: SafeHouse port (AIJOB) - the follow / attack job */
    /* 0x1c */ char pad2[0x30 - 0x1C];
    /* 0x30 */ void *ploFollow;               /* field: SafeHouse port */
    /* 0x34 */ char pad3[0x50 - 0x34];
    /* 0x50 */ qword posFollow;               /* field: SafeHouse port - where the path was planned to */
    /* 0x60 */ int st;                        /* field: SafeHouse port */
    /* 0x64 */ char pad4[0x6C - 0x64];
    /* 0x6c */ float sNear;                   /* field: SafeHouse port */
    /* 0x70 */ float sFar;                    /* field: SafeHouse port */
    /* 0x74 */ float svNear;                  /* field: SafeHouse port */
    /* 0x78 */ float svFar;                   /* field: SafeHouse port */
    /* 0x7c */ char pad5[0x90 - 0x7C];
    /* 0x90 */ struct GUARD *ploEnemy;        /* field: SafeHouse port */
};
#include "cid.h"
extern float D_002A4E34;          /* FLT_MAX */
extern struct LM D_002BD330;      /* 0..600: an enemy close enough to attack */
extern struct LM D_002BD338;      /* 0..1200: an enemy close enough to keep attacking */
extern float D_002BD340;          /* 200: the followed object's move that plans the path again */
void Update__5AIJOB(struct JOBCOMPANION *pjob);
int FJobDone(struct JOBCOMPANION *pjob) asm("FJobDone__FP5AIJOB");
qword PosOfLo__FP2LO(void *p);
struct GUARD *FindEnemy__12JOBCOMPANION(struct JOBCOMPANION *pjob);
int FNeedRecover__12JOBCOMPANION(struct JOBCOMPANION *pjob);
int FCheckLm(struct LM *plm, float g) asm("FCheckLm__FP2LMf");
void SetState__12JOBCOMPANIONi(struct JOBCOMPANION *pjob, int st);
int func_00132EA0(void *plo);   /* the object's class id */
int func_00145DA0(void *pjob);   /* JOBMURRAYATTACK done */
int func_00146298(void *pjob);   /* JOBBENTLEYATTACK done */
int func_00146790(void *pjob);   /* JOBSLYATTACK done */
void PlanFollow__12JOBCOMPANION(struct JOBCOMPANION *pjob);
void SetAsegaSpeed(void *pasega, float svu) asm("SetAsegaSpeed__FP5ASEGAf");

static __inline__ float LenXY(qword d)
{
    float g;
    qword t;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d));
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ float Len(qword d)
{
    qword t;
    float g;
    __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ void GClamp(float *pg, float lo, float hi) { if (*pg < lo) *pg = lo; else if (hi < *pg) *pg = hi; }
static __inline__ int FFar(qword a, qword b) { float lim = D_002BD340; return lim < LenXY(Sub(a, b)); }

// name: SafeHouse port (JOBCOMPANION::Update)
void Update__12JOBCOMPANION(struct JOBCOMPANION *pjob)
{
    struct ACTOR *pactor;
    qword posActor, posFollow;
    float sxyFollow, sEnemy;
    struct GUARD *pguard;
    void *ploFollow;
    Update__5AIJOB(pjob);
    pactor = pjob->pactor;
    ploFollow = pjob->ploFollow;
    posActor = PosOfLo__FP2LO(pactor);
    posFollow = PosOfLo__FP2LO(ploFollow);
    sxyFollow = LenXY(Sub(posActor, posFollow));
    pguard = FindEnemy__12JOBCOMPANION(pjob);
    if (pguard) {
        qword posEnemy = PosOfLo__FP2LO(pguard);
        float sFromActor = Len(Sub(posEnemy, posActor));
        float sFromFollow = Len(Sub(posEnemy, posFollow));
        sEnemy = sFromActor < sFromFollow ? sFromActor : sFromFollow;
    } else {
        sEnemy = D_002A4E34;
    }
    while (!FJobDone(pjob)) {
        int stOld = pjob->st;
        int f;   /* a recovery is needed */
        switch (stOld) {
        case 0:
            f = FNeedRecover__12JOBCOMPANION(pjob) != 0;
            if (f)
                SetState__12JOBCOMPANIONi(pjob, 1);
            else if (FCheckLm(&D_002BD330, sEnemy)) {
                pjob->ploEnemy = pguard;
                SetState__12JOBCOMPANIONi(pjob, 2);
            }
            break;
        case 1:
            if (pjob->pactor->stJump == -1)
                SetState__12JOBCOMPANIONi(pjob, 0);
            break;
        case 2:
            f = FNeedRecover__12JOBCOMPANION(pjob) != 0;
            if (f)
                SetState__12JOBCOMPANIONi(pjob, 1);
            else if (!FCheckLm(&D_002BD338, sEnemy))
                SetState__12JOBCOMPANIONi(pjob, 0);
            else {
                switch (func_00132EA0(pjob->pactor)) {
                case CID_MURRAY:
                    if (func_00145DA0(pjob->pchild))
                        SetState__12JOBCOMPANIONi(pjob, 0);
                    break;
                case CID_BENTLEY:
                    if (func_00146298(pjob->pchild))
                        SetState__12JOBCOMPANIONi(pjob, 0);
                    break;
                case CID_JT:
                    if (func_00146790(pjob->pchild))
                        SetState__12JOBCOMPANIONi(pjob, 0);
                    break;
                }
            }
            break;
        }
        if (pjob->st == stOld)
            break;
    }
    if (pjob->st == 0) {
        struct REGENT *pregent = pjob->pactor->psost ? pjob->pactor->psost->pregent : 0;
        void *preg = pregent ? pregent->preg : 0;
        if (!preg)
            pjob->pchild->fNoAvoid = 1;
        if (FFar(pjob->posFollow, posFollow))
            PlanFollow__12JOBCOMPANION(pjob);
        if (pactor->pasega) {
            float u = (sxyFollow - pjob->sNear) / (pjob->sFar - pjob->sNear);
            GClamp(&u, 0.0f, 1.0f);
            SetAsegaSpeed(pactor->pasega, (1.0f - u) * pjob->svNear + u * pjob->svFar);
        }
    }
}
