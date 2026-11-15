/* CRef::SetBifk: drops the old payload and makes the reference the built-in function bifk. */
#include "splice.h"
// name: SafeHouse port (CRef::SetBifk)
CRef *SetBifk__4CRef4BIFK(CRef *pref, int bifk)
{
    Decref__4CRef(pref);
    pref->m_tag.m_n = bifk;
    pref->m_tagk = TAGK_Bifk;
    return pref;
}
