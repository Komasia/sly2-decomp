#include "splicewrap.h"
void CutCm(s32) asm("CutCm__FP2CM");                         /* extern */
CRef *func_00102768(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, 0x24);
    CutCm(pbasic);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
