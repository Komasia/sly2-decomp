/* class: GUARD (SafeHouse guardstart.cpp: EOPIDs 315 / 316, the detector's view volumes +0xE8 / +0xEC at run time). */
#include "stepguard.h"
struct DETECTOR {
    /* 0x00 */ char pad0[0xe8];
    /* 0xe8 */ int pvolA;
    /* 0xec */ int pvolB;
};

void func_00259D48(struct GUARD *pguard, int n)
{
    pguard->pdet->pvolB = n;
}
