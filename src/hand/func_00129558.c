/* CRef::SetF32: drops the old payload and makes the reference the float g. */
#include "splice.h"
// name: SafeHouse port (CRef::SetF32)
CRef *SetF32__4CReff(CRef *pref, float g)
{
    Decref__4CRef(pref);
    pref->m_tag.m_g = g;
    pref->m_tagk = TAGK_F32;
    return pref;
}
