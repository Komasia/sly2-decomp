/* func_002087C8 (0x2087C8): the guard's detector entries less the generated ones; its target classes (+0x394) and
 * the generated count (+0x3A4) cleared (SafeHouse launcher.cpp). */
#include "stepguard.h"
struct DETECTOR {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int cdetentry;
};

void func_002087C8(struct GUARD *pguard)
{
    struct DETECTOR *pdet = pguard->pdet;
    pdet->cdetentry -= pguard->cdetentryGenerated;
    pguard->ccidTarget = 0;
    pguard->cdetentryGenerated = 0;
}
