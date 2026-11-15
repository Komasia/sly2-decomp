/* JOBRAIL::Update: moving along the rail: the guard's place on the rail's curve (+0xF88) advanced toward the goal
 * (D_002BE74C ahead, wrapped) from the nearest point to the guard; at the goal: done (state 1); otherwise the guard
 * heads along the curve's direction (reversed when going back) and its walk clip plays at the job's speed.
 * Repeats while the state changes. */
#include "h2_aijobs.h"

extern float D_002BE74C;                /* the look-ahead along the rail */
struct CRV;
struct ASEGA;
struct MOVEREF { struct AIJOB *pjob; int fHeadingLocked; int n8; struct GUARD *pguard; };  /* field: SafeHouse port */
struct GUARD {
    /* 0x000 */ char pad0[0xF84];
    /* 0xf84 */ struct CRV *pcrvMove;   /* field: SafeHouse port (ploMove) - the rail it moves on */
    /* 0xf88 */ float sMove;            /* field: SafeHouse port - its place along the rail */
    /* 0xf8c */ int fForward;           /* field: SafeHouse port (nMoveKind) - moving toward the rail's end */
    /* 0xf90 */ char padF90[0xFD0 - 0xF90];
    /* 0xfd0 */ struct MOVEREF move;    /* field: SafeHouse port */
};
struct KINDE { int k; void *pv; struct ASEGA *pasega; int grf; };   /* field: SafeHouse port (guard.h KINDE) */
void Update__5AIJOB(JOBRAIL *pjob);
qword PosOfLo__FP2LO(struct GUARD *pguard);
float SWrapCrv__FP3CRVf(struct CRV *pcrv, float s);
void NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(struct CRV *pcrv, float s, qword pos, int a, int b, QVEC *pdir, int c, float *ps);
int func_0017CE30(JOBRAIL *pjob);
void SetRailState__7JOBRAILi(JOBRAIL *pjob, int st);
float atan2f(float y, float x);
void SetMoveHeading__FP7MOVEREF(struct MOVEREF *pmove, float rad);
void SetAsegaSpeed(struct ASEGA *pasega, float svt) asm("SetAsegaSpeed__FP5ASEGAf");

// name: SafeHouse port (JOBRAIL::Update)
void Update__7JOBRAIL(JOBRAIL *pjob)
{
    int st;
    Update__5AIJOB(pjob);
    do {
        st = pjob->st;
        if (st == 0) {
            struct GUARD *pguard = pjob->aijob.pguard;
            struct CRV *pcrv = pguard->pcrvMove;
            float s = pguard->sMove;
            qword pos;
            QVEC dir;
            pguard->fForward = s < pjob->sGoal;
            pos = PosOfLo__FP2LO(pjob->aijob.pguard);
            NearestCrvS__FP3CRVG9VU_VECTORPvP6VECTORT3PfT5f(pcrv, SWrapCrv__FP3CRVf(pcrv, pjob->aijob.pguard->fForward ? s + D_002BE74C : s - D_002BE74C), pos, 0, 0, &dir, 0, &s);
            pjob->aijob.pguard->sMove = s;
            if (func_0017CE30(pjob)) {
                SetRailState__7JOBRAILi(pjob, 1);
            } else {
                if (pjob->aijob.pguard->fForward == 0) {
                    /* going back: face against the curve */
                    qword dirFwd = dir.q;
                    QVEC minus;
                    __asm__("qmtc2.ni %1, %0" : "=j"(minus.q) : "r"(-1.0f));
                    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(dir.q) : "j"(dirFwd), "j"(minus.q));
                }
                SetMoveHeading__FP7MOVEREF(&pjob->aijob.pguard->move, atan2f(dir.f[1], dir.f[0]));
                SetAsegaSpeed(((JOBMOVE *)pjob->aijob.pchild)->pkinde->pasega, pjob->uSpeed);
            }
        }
    } while (pjob->st != st);
}
