/* JOBCOMPANION::FNeedRecover: whether the companion must be recovered to the followed object: it is in a navigation
 * region other than the actor's (not the region of oid 0x2CA), not jumping (an actor), its position is on that
 * region's navigation and there is ground under it; the point found is kept for the recovery (+0x80).
 * Layout: SafeHouse port (actorai.h JOBCOMPANION, actorai.cpp FNeedRecover). */
#include "actor.h"
#include "cid.h"
struct NAVREGION { char pad[0x18]; int oid; };   /* +0x18 compared with oid 0x2CA (SafeHouse: its mesh's oid) */
struct REGENT { char pad[0x10]; struct NAVREGION *preg; };
struct LOFOLLOW { char pad[0x2DC]; int stJump; };   /* an actor's jump.state (-1 when not jumping) */
struct JOBCOMPANION {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct ACTOR *pactor;        /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ struct LOFOLLOW *ploFollow;  /* field: SafeHouse port */
    /* 0x34 */ char pad3[0x80 - 0x34];
    /* 0x80 */ qword posRecover;            /* field: SafeHouse port */
};
#define OID_NoRecoverRegion 0x2CA
struct NAVREGION *func_00145AA8(struct JOBCOMPANION *pjob);   /* the followed object's region */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *plo, int cid);
qword PosOfLo__FP2LO(void *plo);
int func_001C09A0(struct NAVREGION *preg, qword pos, int n);  /* the position is on the region's navigation */
int FDropOnGround__FP6VECTORffiPv(qword *ppos, float sUp, float sDown, int n, int pv);
// name: SafeHouse port (JOBCOMPANION::FNeedRecover)
int FNeedRecover__12JOBCOMPANION(struct JOBCOMPANION *pjob)
{
    struct NAVREGION *preg = func_00145AA8(pjob);
    struct REGENT *pregent;
    struct NAVREGION *pregActor;
    qword pos;
    if (!preg) return 0;
    pregent = pjob->pactor->so.psophys ? pjob->pactor->so.psophys->pregent : 0;
    pregActor = pregent ? pregent->preg : 0;
    if (preg == pregActor) return 0;
    if (preg->oid == OID_NoRecoverRegion) return 0;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pjob->ploFollow, CID_ACTOR) && pjob->ploFollow->stJump != -1) return 0;
    pos = PosOfLo__FP2LO(pjob->ploFollow);
    if (!func_001C09A0(preg, pos, 0)) return 0;
    if (!FDropOnGround__FP6VECTORffiPv(&pos, 100.0f, -150.0f, 0, 0)) return 0;
    pjob->posRecover = pos;
    return 1;
}
