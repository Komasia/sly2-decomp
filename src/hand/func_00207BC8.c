/* func_00207BC8 (0x207BC8): the live splice method 243 (0x102B60): SetGuardKinde, then the entry resolved at once. */
#include "h6_guard.h"
struct GUARD;
unsigned long MaskOfList__FPv(void *plist);
KINDE *PkindeOfMask__FP5GUARDUl(struct GUARD *pguard, unsigned long grf);
void SetGuardKinde__FP5GUARD3OIDii(struct GUARD *pguard, void *plist, int oid, int grf);
void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, struct GUARD *pguard);

void func_00207BC8(struct GUARD *pguard, void *plist, int oid, int grf)
{
    KINDE *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plist));
    SetGuardKinde__FP5GUARD3OIDii(pguard, plist, oid, grf);
    ResolveKinde__FP5KINDEP5GUARD(pkinde, pguard);
}
