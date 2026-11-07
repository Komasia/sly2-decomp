#include "splicewrap.h"
void Pause__4CSnd(s32);                         /* extern */
// name: SafeHouse port (RefSoundMethod)
CRef *RefSoundMethod__FP5BASICiP4CRef(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, 0x24);
    Pause__4CSnd(pbasic);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
