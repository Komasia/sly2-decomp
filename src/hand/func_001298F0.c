/* CRef::SetSmp: drops the old payload and makes the reference a fresh pooled copy of *psmp. */
#include "splice_ref.h"
// name: SafeHouse port (CRef::SetSmp)
CRef *SetSmp__4CRefP3SMP(CRef *pref, SMP *psmp)
{
    REFSMP *p;
    Decref__4CRef(pref);
    pref->m_tagk = TAGK_Smp;
    p = (REFSMP *)func_0011CCC0(&D_004521E8);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFSMP *)pref->m_tag.m_pv)->smp = *psmp;
    return pref;
}
