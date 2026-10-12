#include "splicewrap.h"
void func_00129A10(void *, s32);                 /* extern */
s32 func_001CB250(s32, M2C_UNK);                    /* extern */

CRef *func_0010E2B8(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    func_00129A10(&ref, func_001CB250(pbasic, 0));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
