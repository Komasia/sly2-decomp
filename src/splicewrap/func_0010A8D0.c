#include "splicewrap.h"
void SetBool__4CRefi(void *, s32);                 /* extern */
s32 FActorPoseDone__FP5ACTOR(s32);                             /* extern */

CRef *func_0010A8D0(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    SetBool__4CRefi(&ref, FActorPoseDone__FP5ACTOR(pbasic) != 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
