/* CRef::SetPair: counts a reference to ppair, drops the old payload and makes the reference that list. */
#include "splice.h"
// name: SafeHouse port (CRef::SetPair)
CRef *SetPair__4CRefP5CPair(CRef *pref, CPair *ppair)
{
    ppair->cref++;
    Decref__4CRef(pref);
    pref->m_tag.m_ppair = ppair;
    pref->m_tagk = TAGK_Pair;
    return pref;
}
