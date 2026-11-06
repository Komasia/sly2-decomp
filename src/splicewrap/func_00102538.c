#include "splicewrap.h"
void func_00129558(void *, f32);                 /* extern */
f32 TMusicTop__FPv(s32);                             /* extern */

CRef *func_00102538(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    func_00129558(&ref, TMusicTop__FPv(pbasic));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
