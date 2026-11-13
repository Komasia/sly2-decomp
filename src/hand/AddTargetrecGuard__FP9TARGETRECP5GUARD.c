/* AddTargetrecGuard: a guard pursuing a target joins its record; the first one starts the record's time and timer.
 * Layout: SafeHouse port (aipursuit.h TARGETREC). */
#include "clock.h"

struct GUARD;
struct TARGETREC {
    /* 0x00 */ float t0;               /* field: SafeHouse port - when the first guard came */
    /* 0x04 */ char pad4[0x28 - 0x4];
    /* 0x28 */ int cpguard;            /* field: SafeHouse port */
    /* 0x2c */ struct GUARD *apguard[1];   /* field: SafeHouse port - the guards pursuing it */
};
void SetTargetrecTimer__FP9TARGETRECi(struct TARGETREC *ptrec, int n);

// name: SafeHouse port (AddTargetrecGuard)
void AddTargetrecGuard__FP9TARGETRECP5GUARD(struct TARGETREC *ptrec, struct GUARD *pguard)
{
    if (ptrec->cpguard == 0) {
        ptrec->t0 = g_clock.t;
        SetTargetrecTimer__FP9TARGETRECi(ptrec, 0);
    }
    ptrec->apguard[ptrec->cpguard++] = pguard;
}
