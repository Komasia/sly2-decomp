/* SetGuardKind3 (0x207C48, splice method 244 {indices, four oids}): the kind entry of the states becomes a new
 * KIND3 with the four directions' ASEG oids (ApplyAseg flags 8). */
#include "h6_guard.h"
long MaskOfList__FPv(int plist);
KINDE *PkindeOfMask__FP5GUARDUl(void *pguard, long grf);
KIND3 *func_0020CA00(int cb);         /* new */
void func_0020C7D8(KIND3 *pk3);       /* KIND3 init */
// name: SafeHouse port (SetGuardKind3)
void SetGuardKind3__FP5GUARDiiiii(void *pguard, int plist, int oid0, int oid1, int oid2, int oid3)
{
    KINDE *pkinde = PkindeOfMask__FP5GUARDUl(pguard, MaskOfList__FPv(plist));
    pkinde->k = KINDK_Kind3;
    pkinde->u.pk3 = func_0020CA00(sizeof(KIND3));
    func_0020C7D8(pkinde->u.pk3);
    pkinde->u.pk3->ae[0].u.oid = oid0;
    pkinde->u.pk3->ae[1].u.oid = oid1;
    pkinde->u.pk3->ae[2].u.oid = oid2;
    pkinde->u.pk3->ae[3].u.oid = oid3;
    pkinde->grf = 8;
}
