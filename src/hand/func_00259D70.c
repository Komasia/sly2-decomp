/* class: GUARD (SafeHouse guardstart.cpp: EOPID 316's getter, the detector's view volume +0xEC). */
#include "stepguard.h"
struct DETECTOR {
    /* 0x00 */ char pad0[0xec];
    /* 0xec */ int pvolB;
};

int func_00259D70(struct GUARD *pguard)
{
    return pguard->pdet->pvolB;
}
