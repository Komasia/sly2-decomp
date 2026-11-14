#include "splicewrap.h"
#include "vtbl.h"
/* splice binding: calls the object's vtable entry 76 */
void SetBool__4CRefi(void *, s32);                 /* extern */
CRef *func_0010BC88(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    VTENT *avte;
    aotyp[0] = 0x1011;
    RefSetArgsFromSplice__FiP4CRefP4OTYPe(&ref, 1, aref, aotyp, &arg0_v);
    avte = *(VTENT **)((char *)pbasic + 0xC);   /* the vtable */
    SetBool__4CRefi(&ref, ((s32 (*)(void *, s32))avte[76].pfn)(VT_THIS(pbasic, &avte[76]), arg0_v) != 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
