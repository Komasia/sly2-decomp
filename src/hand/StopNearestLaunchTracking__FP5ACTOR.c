/* StopNearestLaunchTracking: the actor's nearest target (+0x10DC, a guard) has its launch job (JOBB1, 0xB1) stop
 * tracking this actor (+0x60) when the job is this actor's. Layout: SafeHouse port (actor.h, aijobs.h JOBB1). */
struct JOBB1 {
    /* 0x00 */ char pad0[0x5c];
    /* 0x5c */ struct ACTOR *ploOwner;   /* field: SafeHouse port */
    /* 0x60 */ int fTrack;               /* field: SafeHouse port */
};
struct GUARD {
    /* 0x000 */ char pad0[0x26c];
    /* 0x26c */ char ajobs[4];           /* the AI job stack */
};
struct ACTOR {
    /* 0x0000 */ char pad0[0x10dc];
    /* 0x10dc */ struct GUARD *plo10DC;  /* field: SafeHouse port - the nearest */
};
struct JOBB1 *PjobFind__FP5GUARDPv(void *pjobs, int cid);

// name: SafeHouse port (StopNearestLaunchTracking)
void StopNearestLaunchTracking__FP5ACTOR(struct ACTOR *pactor)
{
    struct GUARD *pguard = pactor->plo10DC;
    if (pguard != 0) {
        struct JOBB1 *pjob = PjobFind__FP5GUARDPv(pguard->ajobs, 0xB1);
        if (pjob != 0 && pjob->ploOwner == pactor)
            pjob->fTrack = 0;
    }
}
