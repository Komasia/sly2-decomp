/* CRef::SetBool: drops the old payload and makes the reference the boolean fBool. */
#include "splice.h"
// name: SafeHouse port (CRef::SetBool)
CRef *SetBool__4CRefi(CRef *pref, int fBool)
{
    Decref__4CRef(pref);
    pref->m_tag.m_bool = fBool;
    pref->m_tagk = TAGK_Bool;
    return pref;
}
