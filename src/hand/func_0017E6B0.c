/* JOBLINK::SetState: the child job ends; at a record: walked: the guard's curve set straight to the record's point
 * and a JOBFOLLOW along it (no avoiding, arrival within 10), with a deadline of the length / the walk speed (at
 * least the minimum); jumped: a JOBUSE to it (0x17E628); straight to it: a JOBNAVPOINT to the record. */
#include "clock.h"
#include "vtbl.h"
#include "cid.h"
#include "h2_aijobs.h"

extern float D_002BE7B0;   /* the walk speed of the deadline (75) */
extern float D_002BE7B4;   /* the least deadline (2) */
/* a pushed child job, as seen through its vtable: JOBNAVPOINT (+0x30 goal), JOBFOLLOW (+0x40 fNoAvoid, +0x64 the
 * arrival distance) */
struct JOBVT {
    char pad0[0xC]; VTENT *vt; char pad10[0x20];
    qword q30; union { qword q; int fNoAvoid; } u40; char pad50[0x14]; float sArrive;
};
/* the guard's curve: its points */
struct CRV { char pad0[0xE8]; int cpos; char padEC[8]; qword *apos; };
struct GUARD {
    /* 0x000 */ char pad0[0x294];
    /* 0x294 */ struct CRV *pcrv;       /* field: SafeHouse port (crv294) - the curve its paths are written to */
};
void EndChildJob__FPP5AIJOB(struct AIJOB **ppjob);
struct JOBVT *func_00205438(struct GUARD *pguard, int cid);   /* SafeHouse port: PjobPush - a child job of the class */
qword PosOfLo__FP2LO(struct GUARD *pguard);
qword PosGoal__FP4GOALG9VU_VECTOR(GOAL *pgoal, qword posFrom);
void RecalcCrv__FP3CRV(struct CRV *pcrv);
void Follow__9JOBFOLLOWP3CRVi(struct JOBVT *pjobFollow, struct CRV *pcrv, int n);
void func_0017E628(JOBLINK *pjob);   /* a JOBUSE to the record */

// name: SafeHouse port (JOBLINK::SetState)
void SetState__7JOBLINKi(JOBLINK *pjob, int st)
{
    if (st == pjob->st) return;
    EndChildJob__FPP5AIJOB(&pjob->aijob.pchild);
    pjob->st = st;
    pjob->tSt = g_clock.t;
    switch (st) {
    case LINKS_Record:
        switch (pjob->plink->kind) {
        case NAVLINKK_Walked:
            {
                struct JOBVT *pjobFollow = func_00205438(pjob->aijob.pguard, CID_JOBFOLLOW);
                struct CRV *pcrv = pjob->aijob.pguard->pcrv;
                qword posGuard = PosOfLo__FP2LO(pjob->aijob.pguard);
                qword posRec = PosGoal__FP4GOALG9VU_VECTOR(&pjob->plink->agoal[pjob->irec], posGuard);
                qword d;
                float len;
                float t = g_clock.t;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(posGuard), "j"(posRec));
                __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
                __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
                __asm__("qmfc2.ni %0, %1" : "=r"(len) : "j"(d));
                {
                    float dt = len / D_002BE7B0;
                    pjob->tEnd = t + (dt < D_002BE7B4 ? D_002BE7B4 : dt);
                }
                pcrv->cpos = 2;
                pcrv->apos[0] = posGuard;
                pcrv->apos[1] = posRec;
                RecalcCrv__FP3CRV(pcrv);
                pjobFollow->u40.fNoAvoid = 1;
                pjobFollow->sArrive = 10.0f;
                Follow__9JOBFOLLOWP3CRVi(pjobFollow, pcrv, 0);
                { VTENT *pvte = &pjobFollow->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobFollow, pvte)); }
            }
            break;
        case NAVLINKK_Jumped:
            func_0017E628(pjob);
            break;
        }
        break;
    case LINKS_Point:
        {
            struct JOBVT *pjobPoint = func_00205438(pjob->aijob.pguard, CID_JOBNAVPOINT);
            qword *aqRec = (qword *)&pjob->plink->agoal[pjob->irec];   /* the record's goal, as two quadwords */
            pjobPoint->q30 = aqRec[0];
            pjobPoint->u40.q = aqRec[1];
            { VTENT *pvte = &pjobPoint->vt[8]; ((void (*)(void *))pvte->pfn)(VT_THIS(pjobPoint, pvte)); }
        }
        break;
    }
}
