/* func_002088E0 (0x2088E0, EOPID 266 via 0x103730): clears the guard's detector entries, its target classes and the
 * generated count, then its excluded (0x2089E8) and immediate (0x208B30) classes. */
#include "stepguard.h"
struct DETECTOR {
    /* 0x00 */ char pad0[0xfc];
    /* 0xfc */ int cdetentry;
};
void func_002089E8(struct GUARD *pguard);
void func_00208B30(struct GUARD *pguard);

void func_002088E0(struct GUARD *pguard)
{
    pguard->pdet->cdetentry = 0;
    pguard->ccidTarget = 0;
    pguard->cdetentryGenerated = 0;
    func_002089E8(pguard);
    func_00208B30(pguard);
}
