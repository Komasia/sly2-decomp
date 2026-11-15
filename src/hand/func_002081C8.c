/* func_002081C8 (0x2081C8): the guard's three 26-entry kind arrays (+0xC10, +0x8D0, +0xA70) cleared (0x208178);
 * InitStepguard calls it. */
#include "h6_guard.h"
typedef struct GUARD GUARD;

void func_00208178(GUARD *pguard, KINDE *akinde);

void func_002081C8(GUARD *pguard)
{
    func_00208178(pguard, (KINDE *)((char *)pguard + 0xC10));
    func_00208178(pguard, (KINDE *)((char *)pguard + 0x8D0));
    func_00208178(pguard, (KINDE *)((char *)pguard + 0xA70));
}
