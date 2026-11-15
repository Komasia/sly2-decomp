/* CRef::SetSymid: drops the old payload and makes the reference the symbol symid. */
#include "splice.h"
// name: SafeHouse port (CRef::SetSymid)
CRef *SetSymid__4CRefUi(CRef *pref, int symid)
{
    Decref__4CRef(pref);
    pref->m_tag.m_symid = symid;
    pref->m_tagk = TAGK_Symid;
    return pref;
}
