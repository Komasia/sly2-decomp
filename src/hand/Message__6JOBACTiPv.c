/* JOBACT::Message (AIJOB vt slot 13): message 0xB from the action's target (+0x30) whose hitter (0x174898) is this
 * guard marks the target hit (+0x40); everything else goes to the base. Layout: SafeHouse port (aipursuit.h JOBACT). */
#include "aijob.h"

struct LO;
struct MSGHIT {
    /* 0x0 */ int x0;
    /* 0x4 */ struct LO *plo;       /* the target */
};
struct JOBACT {
    /* 0x00 */ AIJOB aijob;
    /* 0x24 */ char pad24[0x30 - 0x24];
    /* 0x30 */ struct LO *ptarget;  /* field: SafeHouse port */
    /* 0x34 */ char pad34[0x40 - 0x34];
    /* 0x40 */ int fHit;            /* field: SafeHouse port */
};
struct GUARD *func_00174898(struct LO *plo);   /* the guard that hit the target */
int Message__5AIJOBiPv(struct JOBACT *pjob, int msg, void *pv);

// name: SafeHouse port (JOBACT::Message)
int Message__6JOBACTiPv(struct JOBACT *pjob, int msg, struct MSGHIT *pmsg)
{
    if (msg == 0xB) {
        struct LO *plo = pmsg->plo;
        if (plo == pjob->ptarget) {
            if (func_00174898(plo) == pjob->aijob.pguard) {
                pjob->fHit = 1;
                return 1;
            }
        }
    }
    return Message__5AIJOBiPv(pjob, msg, pmsg);
}
