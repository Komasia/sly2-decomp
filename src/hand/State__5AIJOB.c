/* AIJOB::State (AIJOB vt slot 12, the base's): 7 unless the guard's +0x204 is set, then 0. */
#include "aijob.h"

struct GUARD {
    /* 0x000 */ char pad0[0x204];
    /* 0x204 */ int f204;
};

// name: SafeHouse port (AIJOB::State)
int State__5AIJOB(AIJOB *pjob)
{
    return pjob->pguard->f204 ? 0 : 7;
}
