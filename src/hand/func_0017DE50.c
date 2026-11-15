/* JOBBD::Update: steps the states until they settle: alerted -> away once the move is done; away: held still ->
 * held; the time left runs down, then goes on while the guard's target is still the object and in reach (the time
 * renewed), else the job ends; held -> away again when let go. While away, the point is chosen again after a while
 * when the guard has reached it or the object came near. */
#include "clock.h"
#include "vtbl.h"
#include "h2_aijobs.h"

extern float D_002BE760;   /* how long a chosen point is kept */
extern float D_002BE764;   /* near the point */
extern float D_002BE768;   /* the object too near */
struct GUARD { char pad0[0xC]; VTENT *vt; };
void Update__5AIJOB(JOBBD *pjob);
int FJobDone(JOBBD *pjob) asm("FJobDone__FP5AIJOB");
int func_00174FB8(AIJOB *pjobMove);                 /* JOBMOVE: done */
int func_00209098(struct GUARD *pguard);            /* the guard is held still */
void SetState__5JOBBDi(JOBBD *pjob, int st);
int func_00208B38(struct GUARD *pguard, struct LO *plo);
float func_00208BB0(struct GUARD *pguard);
qword PosOfLo__FP2LO(void *plo);
qword PosGoal__FP4GOALG9VU_VECTOR(GOAL *pgoal, qword posFrom);
void ChooseAway__5JOBBD(JOBBD *pjob);
/* the horizontal distance between two points */
static __inline__ float Dist(qword a, qword b) {
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    return f;
}

// name: SafeHouse port (JOBBD::Update)
void Update__5JOBBD(JOBBD *pjob)
{
    int st;
    Update__5AIJOB(pjob);
    while (st = pjob->st, !FJobDone(pjob)) {
        switch (pjob->st) {
        case BDS_Alerted:
            if (func_00174FB8(pjob->aijob.pchild)) SetState__5JOBBDi(pjob, BDS_Away);
            break;
        case BDS_Away:
            if (func_00209098(pjob->aijob.pguard)) {
                SetState__5JOBBDi(pjob, BDS_Held);
            } else {
                { float dt = g_clock.dt; pjob->tLeft -= dt; }
                if (pjob->tLeft <= 0.0f) {
                    struct LO *ploTarget;
                    { struct GUARD *pguard = pjob->aijob.pguard; VTENT *pvte = &pguard->vt[0x58]; ploTarget = ((struct LO *(*)(void *))pvte->pfn)(VT_THIS(pguard, pvte)); }
                    if (ploTarget == pjob->ploFrom && func_00208B38(pjob->aijob.pguard, ploTarget)) {
                        pjob->tLeft = func_00208BB0(pjob->aijob.pguard);
                    } else {
                        SetState__5JOBBDi(pjob, BDS_None);
                    }
                }
            }
            break;
        case BDS_Held:
            if (!func_00209098(pjob->aijob.pguard)) SetState__5JOBBDi(pjob, BDS_Away);
            break;
        }
        if (pjob->st != st) continue;
        break;
    }
    if (pjob->st == BDS_Away) {
        JOBGOTO *pjobGoto = (JOBGOTO *)pjob->aijob.pchild;
        if (g_clock.t - pjob->tChoose > D_002BE760) {
        GOAL *pgoal = &pjobGoto->goal;
        qword posGuard = PosOfLo__FP2LO(pjob->aijob.pguard);
        int fChoose = 0;
        qword posGoal = PosGoal__FP4GOALG9VU_VECTOR(pgoal, posGuard);
        if (Dist(PosOfLo__FP2LO(pjob->aijob.pguard), posGoal) < D_002BE764) {
            fChoose = 1;
        } else if (Dist(PosOfLo__FP2LO(pjob->aijob.pguard), PosOfLo__FP2LO(pjob->ploFrom)) < D_002BE768) {
            fChoose = 1;
        }
        if (fChoose) ChooseAway__5JOBBD(pjob);
        }
    }
}
