#include "splicewrap.h"
void PostHit__FP2LOii(s32, M2C_UNK, M2C_UNK);       /* extern */
CRef *func_0010D158(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, 0x24);
    PostHit__FP2LOii(pbasic, 0, 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
