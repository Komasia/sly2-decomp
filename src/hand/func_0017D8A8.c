/* JOBGOTO (SafeHouse: Target17D8A8, orig 0x17D8A8): the current goal: the goal itself; unless going straight, when
 * the goal lies in another navigation region, the link path to it (exact, else - if allowed - inexact) and the
 * nearest point of the goal in the region the link leads to; no region / no path: the guard's own position. */
#include "h2_aijobs.h"

struct NAVSERIAL;
struct SW { char pad0[0x45CC]; struct NAVSERIAL *pnavserial; };
extern struct SW g_sw;
/* the guard's fields used here */
struct NAV { char pad0[0x10]; struct NAVREGION *pnavregion; };
struct SOPHYS { char pad0[0xDC]; struct NAV *pnav; };
struct GUARD {
    /* 0x000 */ char pad0[0xE8];
    /* 0x0e8 */ struct SOPHYS *pE8;     /* -> +0xDC -> +0x10: the navigation region it is in */
};
qword PosOfLo__FP2LO(struct GUARD *pguard);
qword PosGoal__FP4GOALG9VU_VECTOR(GOAL *pgoal, qword posFrom);
struct NAVREGION *PregionAt__FG9VU_VECTORi(qword pos, int n);
int CNavLinkPath__FP5GUARDP6VECTORG9VU_VECTORiiPP4EDGE(struct NAVSERIAL *pnav, struct GUARD *pguard, qword posTarget,
                                                       int fExact, int cMax, NAVLINK **aplink);
void func_001C0940(struct NAVREGION *pnavregion, qword pos, qword *ppos, int n);   /* the region's nearest point */

void func_0017D8A8(JOBGOTO *pjob)
{
    pjob->cplink = 0;
    pjob->goalCur = pjob->goal;
    if (pjob->fDirect == 0) {
        qword posGuard = PosOfLo__FP2LO(pjob->aijob.pguard);
        qword posGoal = PosGoal__FP4GOALG9VU_VECTOR(&pjob->goal, posGuard);
        struct SOPHYS *psophys = pjob->aijob.pguard->pE8;
        struct NAV *pnav = psophys ? psophys->pnav : 0;
        struct NAVREGION *pregionGuard = pnav ? pnav->pnavregion : 0;
        struct NAVREGION *pregionGoal;
        int fFail;
        pregionGoal = PregionAt__FG9VU_VECTORi(posGoal, 0);
        fFail = 0;
        if (pregionGoal == 0) {
            fFail = 1;
        } else if (pregionGoal != pregionGuard) {
            struct SW *psw = &g_sw;
            int cplink;
            if ((pjob->cplink = CNavLinkPath__FP5GUARDP6VECTORG9VU_VECTORiiPP4EDGE(psw->pnavserial, pjob->aijob.pguard, posGoal, 1, 1, pjob->aplink)) <= 0) {
                if (pjob->fInexact == 0) {
                    fFail = 1;
                } else {
                    cplink = CNavLinkPath__FP5GUARDP6VECTORG9VU_VECTORiiPP4EDGE(psw->pnavserial, pjob->aijob.pguard, posGoal, 0, 1, pjob->aplink);
                    pjob->cplink = cplink;
                    if (cplink == 0) {
                        fFail = 1;
                    } else {
                        struct NAVREGION *pregion;
                        if (pjob->aplink[0] == 0) {
                            pregion = pregionGuard;
                            pjob->cplink = 0;
                        } else {
                            pregion = pjob->aplink[cplink - 1]->pregionEnd;
                        }
                        pjob->goalCur.pcrv = 0;
                        pjob->goalCur.plo = 0;
                        func_001C0940(pregion, posGoal, &pjob->goalCur.pos, 1);
                    }
                }
            }
        }
        if (fFail) {
            pjob->goalCur.pcrv = 0;
            pjob->goalCur.plo = 0;
            pjob->goalCur.pos = posGuard;
        }
    }
}
