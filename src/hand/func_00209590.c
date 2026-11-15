/* func_00209590 (0x209590): after a clone, a guard kind entry gets its own copy of its KIND2 / KIND3 payload. */
#include "h6_guard.h"
KIND2 *func_0020C010(int cb);   /* new KIND2 */
KIND3 *func_0020CA00(int cb);   /* new KIND3 */
void CopyAb(void *pvDst, void *pvSrc, int cb) asm("CopyAb__FPvT0Ui");
void func_00209590(KINDE *pkinde)
{
    void *pv;
    switch (pkinde->k) {
    case KINDK_Kind2:
        pv = func_0020C010(sizeof(KIND2));
        CopyAb(pv, pkinde->u.pk2, sizeof(KIND2));
        pkinde->u.pk2 = pv;
        break;
    case KINDK_Kind3:
        pv = func_0020CA00(sizeof(KIND3));
        CopyAb(pv, pkinde->u.pk3, sizeof(KIND3));
        pkinde->u.pk3 = pv;
        break;
    }
}
