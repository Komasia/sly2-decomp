/* BIF 137: the HUD prompt widget (0x3DA0C0) as a reference. */
#include "splice.h"
void SetBasic__4CRefP5BASIC(CRef *pref, void *p);
extern char D_003DA0C0[];
CRef *func_00125690(CRef *ret)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    SetBasic__4CRefP5BASIC(&ref, D_003DA0C0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
