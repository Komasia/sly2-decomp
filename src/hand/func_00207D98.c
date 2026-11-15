/* func_00207D98 (0x207D98, splice method 245 {indices, oid}): the kind entry of the states becomes a new KIND2 with
 * the ASEG oid (no ApplyAseg flags). */
#include "h6_guard.h"
unsigned long MaskOfList__FPv(void *plist);
KINDE *PkindeOfMask__FP5GUARDUl(void *pguard, unsigned long grf);
KIND2 *func_0020C010(int cb);         /* new */
void func_0020BD78(KIND2 *pk2);       /* KIND2 init */
void func_00207D98(void *pguard, void *plist, int oid)
{
    KINDE *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plist));
    pkinde->k = KINDK_Kind2;
    pkinde->u.pk2 = func_0020C010(sizeof(KIND2));
    func_0020BD78(pkinde->u.pk2);
    pkinde->u.pk2->oid = oid;
    pkinde->grf = 0;
}
