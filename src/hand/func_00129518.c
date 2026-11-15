/* CRef::SetS32: drops the old payload and makes the reference the integer n. */
#include "splice.h"
// name: SafeHouse port (CRef::SetS32)
CRef *SetS32__4CRefi(CRef *pref, int n)
{
    Decref__4CRef(pref);
    pref->m_tag.m_n = n;
    pref->m_tagk = TAGK_S32;
    return pref;
}
