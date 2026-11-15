/* JOBSURROUND::Enter: a guard that walks (+0xFE8 bit 4) starts on a fresh path (its own curve +0x294, from where it
 * stands, in its navigation region) and follows it; otherwise it stands. */
#include "h2_aijobs.h"

struct NAVREGION;
struct CRV;
struct NAV { char pad0[0x10]; struct NAVREGION *pnavregion; };
struct SOPHYS { char pad0[0xDC]; struct NAV *pnav; };
struct GUARD {
    /* 0x000 */ char pad0[0xE8];
    /* 0x0e8 */ struct SOPHYS *pE8;     /* -> +0xDC -> +0x10: the navigation region it is in */
    /* 0x0ec */ char padEC[0x294 - 0xEC];
    /* 0x294 */ struct CRV *pcrv;       /* field: SafeHouse port (crv294) - the curve its paths are written to */
    /* 0x298 */ char pad298[0xFE8 - 0x298];
    /* 0xfe8 */ int grfFE8;             /* field: SafeHouse port */
};
void Enter__5AIJOB(JOBSURROUND *pjob);
qword PosOfLo__FP2LO(struct GUARD *pguard);
void FNavPathCrv__FP9NAVREGIONiiP3CRV(struct NAVREGION *pnavregion, qword posFrom, qword posTo, struct CRV *pcrv);
void SetSurroundState__11JOBSURROUNDi(JOBSURROUND *pjob, int st);

// name: SafeHouse port (JOBSURROUND::Enter)
void Enter__11JOBSURROUND(JOBSURROUND *pjob)
{
    Enter__5AIJOB(pjob);
    if (pjob->aijob.pguard->grfFE8 & 4) {
        struct NAV *pnav = pjob->aijob.pguard->pE8 ? pjob->aijob.pguard->pE8->pnav : 0;
        struct NAVREGION *pnavregion = pnav ? pnav->pnavregion : 0;
        qword pos = PosOfLo__FP2LO(pjob->aijob.pguard);
        FNavPathCrv__FP9NAVREGIONiiP3CRV(pnavregion, pos, PosOfLo__FP2LO(pjob->aijob.pguard), pjob->aijob.pguard->pcrv);
        SetSurroundState__11JOBSURROUNDi(pjob, SURS_Follow);
    } else {
        SetSurroundState__11JOBSURROUNDi(pjob, SURS_Stand);
    }
}
