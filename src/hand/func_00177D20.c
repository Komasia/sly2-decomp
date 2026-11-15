/* class: AIJOB (SafeHouse aijobs.cpp / aihit.cpp (0x177D20): its guard is busy - either of its two object lists
 * +0xF94 / +0xFA8 not empty). */
#include "stepguard.h"
struct AIJOB {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct GUARD *pguard;   /* field: SafeHouse port */
};

int func_00177D20(struct AIJOB *pjob)
{
    struct GUARD *pguard = pjob->pguard;
    int fBusy = 0;
    if (pguard->cploTurnTo != 0 || pguard->cploAttack != 0) {
        fBusy = 1;
    }
    return fBusy;
}
