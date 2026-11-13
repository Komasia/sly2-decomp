/* AIJOB::Drive (AIJOB vt slot 14, the base's): the left stick at rest, pointing along the guard's heading
 * (GUARD +0x1A8). PADCTL layout: SafeHouse port (po.h PADCTL). */
#include "aijob.h"

struct GUARD {
    /* 0x000 */ char pad0[0x1a8];
    /* 0x1a8 */ float radHeading;   /* (SafeHouse ai.h: "rest, facing the owner's heading") */
};
struct PADCTL {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ float radJoy;        /* field: SafeHouse port - the left stick's world heading */
    /* 0x1c */ float uJoy;          /* field: SafeHouse port - its deflection */
};

// name: SafeHouse port (AIJOB::Drive)
void Drive__5AIJOBP6PADCTL(AIJOB *pjob, struct PADCTL *ppadctl)
{
    ppadctl->uJoy = 0.0f;
    ppadctl->radJoy = pjob->pguard->radHeading;
}
