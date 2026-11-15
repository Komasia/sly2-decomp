/* func_00207F50 (0x207F50): SetArrayKindes with each changed entry resolved at once (the live splice methods). */
#include "h6_guard.h"
void func_002090D0(KINDE *pkinde, void *pguard);   /* clears the entry (frees its KIND2 / KIND3) */
void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, void *pguard);
void func_00207F50(void *pguard, int grfEntries, int oid, int grf, KINDE *pkinde)
{
    int i;
    int bit = 1;
    for (i = 25; i >= 0; i--) {
        if (grfEntries & bit) {
            func_002090D0(pkinde, pguard);
            pkinde->u.oid = oid;
            pkinde->grf = grf;
            ResolveKinde__FP5KINDEP5GUARD(pkinde, pguard);
        }
        bit <<= 1;
        pkinde++;
    }
}
