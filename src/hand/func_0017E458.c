/* JOBLINK::Update: while crossing: at the point: on to the next record once there; at a record: jumped: once the
 * jump (JOBUSE) is done, the next record when near it, else straight to it; walked: past the deadline straight to
 * it, else the next record once the guard is in the link's end region and the follower arrived. */
#include "clock.h"
#include "h2_aijobs.h"

/* the guard's fields used here */
struct NAV { char pad0[0x10]; struct NAVREGION *pnavregion; };
struct SOPHYS { char pad0[0xDC]; struct NAV *pnav; };
struct GUARD {
    /* 0x000 */ char pad0[0xE8];
    /* 0x0e8 */ struct SOPHYS *pE8;     /* -> +0xDC -> +0x10: the navigation region it is in */
};
void Update__5AIJOB(JOBLINK *pjob);
int func_0017E570(JOBLINK *pjob);                /* crossed (no state) */
int FDone__11JOBNAVPOINT(AIJOB *pjobPoint);
int func_00174FB8(AIJOB *pjobMove);              /* JOBMOVE: done */
int func_0017E5F0(JOBLINK *pjob);                /* near the current record */
void NextRecord__7JOBLINK(JOBLINK *pjob);
void SetState__7JOBLINKi(JOBLINK *pjob, int st);
int FArrived__9JOBFOLLOW(AIJOB *pjobFollow);

// name: SafeHouse port (JOBLINK::Update)
void Update__7JOBLINK(JOBLINK *pjob)
{
    Update__5AIJOB(pjob);
    if (func_0017E570(pjob)) return;
    switch (pjob->st) {
    case LINKS_Point:
        if (FDone__11JOBNAVPOINT(pjob->aijob.pchild)) NextRecord__7JOBLINK(pjob);
        break;
    case LINKS_Record: {
        NAVLINK *plink = pjob->plink;
        switch (plink->kind) {
        case NAVLINKK_Jumped:
            if (func_00174FB8(pjob->aijob.pchild)) {
                if (func_0017E5F0(pjob)) NextRecord__7JOBLINK(pjob);
                else SetState__7JOBLINKi(pjob, LINKS_Point);
            }
            break;
        case NAVLINKK_Walked:
            if (pjob->tEnd < g_clock.t) {
                SetState__7JOBLINKi(pjob, LINKS_Point);
            } else {
                struct SOPHYS *psophys = pjob->aijob.pguard->pE8;
                struct NAV *pnav = psophys ? psophys->pnav : 0;
                struct NAVREGION *pregion = pnav ? pnav->pnavregion : 0;
                if (pregion == plink->pregionEnd && FArrived__9JOBFOLLOW(pjob->aijob.pchild)) NextRecord__7JOBLINK(pjob);
            }
            break;
        }
        break;
    }
    }
}
