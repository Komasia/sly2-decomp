#include "splicewrap.h"
void func_00129598(void *, s32);                 /* extern */
s32 func_001424D0(s32);                             /* extern */

CRef *func_0010AB88(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    func_00129598(&ref, func_001424D0(pbasic) != 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
