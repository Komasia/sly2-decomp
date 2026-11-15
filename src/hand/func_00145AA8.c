/* class: JOBCOMPANION (called by its PlanFollow / FNeedRecover; SafeHouse actorai.cpp: "0x145AA8: target's region,
 * SOST +0xDC -> +0x10"): the navigation region of the followed object (+0x30) - an SO's from its physics state's
 * region entry (SO::psophys -> SOPHYS::pregent), any other object's from its position. */
#include "so.h"
#include "cid.h"

typedef struct NAVREGION NAVREGION;
/* SOPHYS::pregent: the SO's entry in the navigation regions */
typedef struct REGENT { char pad0[0x10]; NAVREGION *preg; } REGENT;

typedef struct JOBCOMPANION {
    /* 0x00 */ char pad0[0x30];
    /* 0x30 */ LO *ploFollow;   /* field: SafeHouse port */
} JOBCOMPANION;

int FIsBasicDerivedFrom__FP5BASIC3CID(LO *plo, int cid);
qword PosOfLo__FP2LO(LO *plo);
NAVREGION *PregionAt__FG9VU_VECTORi(qword pos, int n);

NAVREGION *func_00145AA8(JOBCOMPANION *pjob)
{
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->ploFollow, CID_SO)) {
        SOPHYS *psophys = ((SO *)pjob->ploFollow)->psophys;
        REGENT *pregent = 0;
        if (psophys != 0) {
            pregent = (REGENT *)psophys->pregent;
        }
        if (pregent != 0) {
            return pregent->preg;
        }
        return 0;
    }
    return PregionAt__FG9VU_VECTORi(PosOfLo__FP2LO(pjob->ploFollow), 1);
}
