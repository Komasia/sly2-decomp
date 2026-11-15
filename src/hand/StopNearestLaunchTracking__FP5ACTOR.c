/* StopNearestLaunchTracking: the actor's nearest target (+0x10DC, a guard) has its launch job (JOBB1, 0xB1) stop
 * tracking this actor (+0x60) when the job is this actor's. Layout: SafeHouse port (actor.h, aijobs.h JOBB1). */
#include "stepguard.h"
#include "actor.h"
struct JOBB1 {
    /* 0x00 */ char pad0[0x5c];
    /* 0x5c */ struct ACTOR *ploOwner;   /* field: SafeHouse port */
    /* 0x60 */ int fTrack;               /* field: SafeHouse port */
};
struct JOBB1 *PjobFind__FP5GUARDPv(void *pjobs, int cid);

// name: SafeHouse port (StopNearestLaunchTracking)
void StopNearestLaunchTracking__FP5ACTOR(struct ACTOR *pactor)
{
    struct GUARD *pguard = (struct GUARD *)pactor->ploFace;   /* the nearest guard */
    if (pguard != 0) {
        struct JOBB1 *pjob = PjobFind__FP5GUARDPv(pguard->step.bhvstk, 0xB1);
        if (pjob != 0 && pjob->ploOwner == pactor)
            pjob->fTrack = 0;
    }
}
