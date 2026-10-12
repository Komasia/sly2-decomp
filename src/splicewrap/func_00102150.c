#include "splicewrap.h"
void func_00129598(void *, s32);                 /* extern */
s32 func_001FE848(s32, s32);                        /* extern */

CRef *func_00102150(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 0x10;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 1, aref, aotyp, &arg0_v);
    func_00129598(&ref, func_001FE848(pbasic, arg0_v) != 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
