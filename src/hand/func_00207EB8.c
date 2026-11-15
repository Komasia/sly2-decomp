/* SetArrayKindes (0x207EB8): in one of the guard's 26-entry kind arrays, each entry selected by grfEntries (bit i =
 * entry i) is cleared (0x2090D0) and gets the object oid and ApplyAseg flags grf. */
#include "h6_guard.h"
void func_002090D0(KINDE *pkinde, void *pguard);   /* clears the entry (frees its KIND2 / KIND3) */
// name: SafeHouse port (SetArrayKindes)
void SetArrayKindes__FPvUi3OIDiT0(void *pguard, int grfEntries, int oid, int grf, KINDE *pkinde)
{
    int i;
    int bit = 1;
    for (i = 25; i >= 0; i--) {
        if (grfEntries & bit) {
            func_002090D0(pkinde, pguard);
            pkinde->u.oid = oid;
            pkinde->grf = grf;
        }
        bit <<= 1;
        pkinde++;
    }
}
