/* JOBACTORWALK::SetGoal: a new goal. While the walk has a follow job (its child), the actor's shared path (+0x294) is
 * set to the goal: a straight line from the actor when it runs or has no navigation region, else a path searched in
 * the region; then the follow job follows it from its start. Layout: SafeHouse port (actorai.cpp SetGoal). */
typedef int qword __attribute__((mode(TI)));
struct NAVREGION;
struct REGENT { char pad[0x10]; struct NAVREGION *preg; };   /* the actor's region entry */
struct SOST { char pad[0xDC]; struct REGENT *pregent; };
/* the path (SafeHouse crv.h CRV): only the points used here */
struct CRV {
    /* 0x00 */ char pad[0xE8];
    /* 0xe8 */ int cpoint;          /* the number of points */
    /* 0xec */ char pad2[0xF4 - 0xEC];
    /* 0xf4 */ qword *apos;         /* field: SafeHouse port - the points */
};
struct ACTOR {
    /* 0x000 */ char pad[0xE8];
    /* 0x0e8 */ struct SOST *psost;
    /* 0x0ec */ char pad2[0x294 - 0xEC];
    /* 0x294 */ struct CRV *pcrv;   /* field: SafeHouse port (crv294) - the path shared by actor jobs */
};
struct JOBACTORWALK {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct ACTOR *pactor;   /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad1[4];
    /* 0x18 */ void *pchild;           /* field: SafeHouse port (AIJOB) - the follow job */
    /* 0x1c */ char pad2[0x30 - 0x1C];
    /* 0x30 */ int fRun;               /* field: SafeHouse port */
    /* 0x34 */ char pad3[0x40 - 0x34];
    /* 0x40 */ qword posGoal;          /* field: SafeHouse port */
};
qword PosOfLo__FP2LO(struct ACTOR *pactor);
void FNavPathCrv__FP9NAVREGIONiiP3CRV(struct NAVREGION *preg, qword posFrom, qword posTo, struct CRV *pcrv);
void RecalcCrv__FP3CRV(struct CRV *pcrv);
void Follow__9JOBFOLLOWP3CRVi(void *pjob, struct CRV *pcrv, int n);
// name: SafeHouse port (JOBACTORWALK::SetGoal)
void SetGoal__12JOBACTORWALKG9VU_VECTOR(struct JOBACTORWALK *pjob, qword posGoal)
{
    pjob->posGoal = posGoal;
    if (pjob->pchild) {
        struct ACTOR *pactor = pjob->pactor;
        struct CRV *pcrv = pactor->pcrv;
        struct REGENT *pregent = pactor->psost ? pactor->psost->pregent : 0;
        struct NAVREGION *preg = pregent ? pregent->preg : 0;
        qword posActor = PosOfLo__FP2LO(pactor);
        if (!preg || pjob->fRun) {
            pcrv->cpoint = 2;
            pcrv->apos[0] = posActor;
            pcrv->apos[1] = pjob->posGoal;
            RecalcCrv__FP3CRV(pcrv);
        } else {
            FNavPathCrv__FP9NAVREGIONiiP3CRV(preg, posActor, pjob->posGoal, pcrv);
        }
        Follow__9JOBFOLLOWP3CRVi(pjob->pchild, pcrv, 0);
    }
}
