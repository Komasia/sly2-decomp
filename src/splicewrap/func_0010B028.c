#include "splicewrap.h"
#include "vtbl.h"
/* splice binding: calls the object's vtable entry 88 */

CRef *func_0010B028(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    VTENT *avte;
    aotyp[0] = 0x1057;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 1, aref, aotyp, &arg0_v);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, TAGK_Void);
    avte = *(VTENT **)((char *)pbasic + 0xC);   /* the vtable */
    ((void (*)(void *, s32))avte[88].pfn)(VT_THIS(pbasic, &avte[88]), arg0_v);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
