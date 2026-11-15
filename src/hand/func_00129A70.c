/* CRef::SetMethod: counts a reference to the bound native method pmethod (its first word is the reference
 * count), drops the old payload and makes the reference that method. */
#include "splice.h"
// name: SafeHouse port (CRef::SetMethod)
CRef *SetMethod__4CRefP7CMethod(CRef *pref, int *pmethod)
{
    (*pmethod)++;
    Decref__4CRef(pref);
    pref->m_tag.m_pv = pmethod;
    pref->m_tagk = TAGK_Method;
    return pref;
}
