#include "splicewrap.h"
void StopScptImpl__FP2LO(s32);                         /* extern */
CRef *func_00106788(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, 0x24);
    StopScptImpl__FP2LO(pbasic);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
