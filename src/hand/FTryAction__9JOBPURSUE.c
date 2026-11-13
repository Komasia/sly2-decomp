/* JOBPURSUE::FTryAction: an action selected against the pursued target (with the guard's target record); none
 * pushes the guard's next try (+0xF04) out by D_002BE610. Layout: SafeHouse port (aipursuit.h JOBPURSUE, guard.h). */
#include "aijob.h"
#include "clock.h"

struct LO;
struct TARGETREC;
struct ACTION;
struct GUARD {
    /* 0x000 */ char pad0[0x3cc];
    /* 0x3cc */ struct TARGETREC *ptarget3CC;   /* field: SafeHouse port */
    /* 0x3d0 */ char pad3D0[0xf04 - 0x3d0];
    /* 0xf04 */ float tF04;                     /* field: SafeHouse port - the next action try */
};
struct JOBPURSUE {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct LO *ptarget;              /* field: SafeHouse port */
    /* 0x34 */ char pad34[0x3c - 0x34];
    /* 0x3c */ struct ACTION *paction;          /* field: SafeHouse port */
};
extern float D_002BE610;   /* SafeHouse: T_SELECT_RETRY */
struct ACTION *PactionSelect__FP5GUARDP2LOP9TARGETREC(struct GUARD *pguard, struct LO *ptarget,
                                                      struct TARGETREC *ptrec);

// name: SafeHouse port (JOBPURSUE::FTryAction)
int FTryAction__9JOBPURSUE(struct JOBPURSUE *pjob)
{
    struct GUARD *pguard = pjob->aijob.pguard;
    struct ACTION *paction = PactionSelect__FP5GUARDP2LOP9TARGETREC(pguard, pjob->ptarget, pguard->ptarget3CC);
    pjob->paction = paction;
    if (paction != 0)
        return 1;
    pguard = pjob->aijob.pguard;
    if (pguard->tF04 < g_clock.t)
        pguard->tF04 = g_clock.t + D_002BE610;
    return 0;
}
