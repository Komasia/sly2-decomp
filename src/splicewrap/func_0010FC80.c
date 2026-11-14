#include "splicewrap.h"
#include "vtbl.h"
/* splice binding: calls the object's vtable entry 83 */

CRef *func_0010FC80(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    VTENT *avte;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 0, aref, NULL);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, TAGK_Void);
    avte = *(VTENT **)((char *)pbasic + 0xC);   /* the vtable */
    ((void (*)(void *))avte[83].pfn)(VT_THIS(pbasic, &avte[83]));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
