/* SetGuardKinde (splice method 243 {indices, oid, grf}): the guard's kind entry of a list of state indices gets a new
 * object (an ASEG / SM / KIND2 / KIND3 by oid, resolved later) and ApplyAseg flags. */
#include "h6_guard.h"
struct GUARD;
unsigned long MaskOfList__FPv(void *plist);
KINDE *PkindeOfMask__FP5GUARDUl(struct GUARD *pguard, unsigned long grf);

// name: SafeHouse port (SetGuardKinde)
void SetGuardKinde__FP5GUARD3OIDii(struct GUARD *pguard, void *plistIndices, int oid, int grf)
{
    KINDE *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plistIndices));
    pkinde->u.oid = oid;
    pkinde->grf = grf;
}
