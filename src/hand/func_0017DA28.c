/* JOBGOTO::Search: chooses the way to the goal (once started, while the guard walks): the current goal; no link:
 * a path to it; a link: a path to its first record, or - a walked link the guard is already next to (within 50,
 * height within 300) - the link itself. The path goes onto the guard's curve (straight when going direct); no path:
 * straight to the point. The search's time and the navigation's serial are remembered. */
#include "clock.h"
#include "h2_aijobs.h"

struct NAVSERIAL { char pad0[0x28]; int nSerial; };
struct SW { char pad0[0x45CC]; struct NAVSERIAL *pnavserial; };
extern struct SW g_sw;
/* the guard's curve: its points */
struct CRV { char pad0[0xE8]; int cpos; char padEC[8]; qword *apos; };
/* the guard's fields used here */
struct NAV { char pad0[0x10]; struct NAVREGION *pnavregion; };
struct SOPHYS { char pad0[0xDC]; struct NAV *pnav; };
struct GUARD {
    /* 0x000 */ char pad0[0xE8];
    /* 0x0e8 */ struct SOPHYS *pE8;     /* -> +0xDC -> +0x10: the navigation region it is in */
    /* 0x0ec */ char padEC[0x294 - 0xEC];
    /* 0x294 */ struct CRV *pcrv;       /* field: SafeHouse port (crv294) - the curve its paths are written to */
    /* 0x298 */ char pad298[0xFE8 - 0x298];
    /* 0xfe8 */ int grfFE8;             /* field: SafeHouse port - 2: it walks */
};
int FJobDone(JOBGOTO *pjob) asm("FJobDone__FP5AIJOB");
void SetState__7JOBGOTOi(JOBGOTO *pjob, int st);
void func_0017D8A8(JOBGOTO *pjob);      /* the current goal */
void func_002562A8(GOAL *pgoal);        /* the goal cleared */
qword PosOfLo__FP2LO(struct GUARD *pguard);
qword PosGoal__FP4GOALG9VU_VECTOR(GOAL *pgoal, qword posFrom);
void PosNearestSegment__FG9VU_VECTORN20P6VECTORN23(qword pos, qword posA, qword posB, qword *pposNearest, float *pu, int n);
void RecalcCrv__FP3CRV(struct CRV *pcrv);
int FNavPathCrv__FP9NAVREGIONiiP3CRV(struct NAVREGION *pnavregion, qword posFrom, qword posTo, struct CRV *pcrv);
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }

// name: SafeHouse port (JOBGOTO::Search)
void Search__7JOBGOTO(JOBGOTO *pjob)
{
    GOAL goal;
    int st;
    if (pjob->st == GOTOS_None) return;
    if (!(pjob->aijob.pguard->grfFE8 & 2)) return;
    if (FJobDone(pjob)) return;
    SetState__7JOBGOTOi(pjob, GOTOS_Search);
    func_0017D8A8(pjob);
    func_002562A8(&goal);
    if (pjob->cplink == 0) {
        goal = pjob->goalCur;
        st = GOTOS_Path;
    } else {
        NAVLINK *plink = pjob->aplink[0];
        goal = plink->agoal[0];
        st = GOTOS_PathOpen;
        if (plink->kind == NAVLINKK_Walked) {
            union { qword q; float f[4]; } posNearest;
            float u;
            qword posGuard = PosOfLo__FP2LO(pjob->aijob.pguard);
            qword posA = PosGoal__FP4GOALG9VU_VECTOR(&plink->agoal[0], posGuard);
            qword posB = PosGoal__FP4GOALG9VU_VECTOR(&plink->agoal[1], posGuard);
            int fNear;
            PosNearestSegment__FG9VU_VECTORN20P6VECTORN23(posGuard, posA, posB, &posNearest.q, &u, 0);
            fNear = 0;
            if (u > 0.0f && u < 1.0f) {
                qword d, l;
                float dist;
                __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(posNearest.q), "j"(posGuard));
                __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(d));
                __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
                __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(l));
                if (dist < 50.0f) {
                    if (__builtin_fabsf(posNearest.f[2] - GetZ(posGuard)) < 300.0f) fNear = 1;
                }
            }
            if (fNear) st = GOTOS_Link;
        }
    }
    if (st > 0) if (st < 3) {
        struct CRV *pcrv = pjob->aijob.pguard->pcrv;
        qword posGuard = PosOfLo__FP2LO(pjob->aijob.pguard);
        qword posGoal = PosGoal__FP4GOALG9VU_VECTOR(&goal, posGuard);
        if (pjob->fDirect) {
            pcrv->cpos = 2;
            pcrv->apos[0] = posGuard;
            pcrv->apos[1] = posGoal;
            RecalcCrv__FP3CRV(pcrv);
        } else {
            struct SOPHYS *psophys = pjob->aijob.pguard->pE8;
            struct NAV *pnav = psophys ? psophys->pnav : 0;
            struct NAVREGION *pregion = pnav ? pnav->pnavregion : 0;
            if (!FNavPathCrv__FP9NAVREGIONiiP3CRV(pregion, posGuard, posGoal, pcrv)) {
                pjob->goalFallback = goal;
                st = GOTOS_Point;
            }
        }
    }
    SetState__7JOBGOTOi(pjob, st);
    pjob->tSearch = g_clock.t;
    pjob->nSerial = g_sw.pnavserial->nSerial;
}
