/* CFrame::RefSetBinding: gives the binding of symid found in pframe or an enclosing frame the value *pref
 * (nothing when unbound); returns void. */
#include "splice.h"
void __as__4CRefRC4CRef(CRef *pref, const CRef *prefSrc);
CRef *PrefFindBinding(CFrame *pframe, unsigned int symid, int fRecurse) asm("PrefFindBinding__6CFrameUii");
// name: SafeHouse port (CFrame::RefSetBinding)
CRef *RefSetBinding__6CFramePvP4CRef(CRef *ret, CFrame *pframe, unsigned int symid, CRef *pref)
{
    CRef ref;
    CRef *prefBinding;
    ref.m_tagk = TAGK_Nil;
    prefBinding = PrefFindBinding(pframe, symid, 1);
    if (prefBinding)
        __as__4CRefRC4CRef(prefBinding, pref);
    Decref__4CRef(&ref);
    InitTag__4CRef(&ref, TAGK_Void);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
