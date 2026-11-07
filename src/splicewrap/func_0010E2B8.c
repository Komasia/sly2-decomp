#include "splicewrap.h"
void SetBasic__4CRefP5BASIC(void *, s32);                 /* extern */
s32 PloAcquireProxyObject__FP2SWi(s32, M2C_UNK);                    /* extern */

CRef *func_0010E2B8(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    SetBasic__4CRefP5BASIC(&ref, PloAcquireProxyObject__FP2SWi(pbasic, 0));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
