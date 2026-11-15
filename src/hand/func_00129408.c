/* CRef::CRef(SMP *): constructs an smp reference holding a fresh pooled copy of *psmp. */
#include "splice_ref.h"
CRef *func_00129408(CRef *pref, SMP *psmp)
{
    REFSMP *p;

    pref->m_tagk = TAGK_Smp;
    p = (REFSMP *)func_0011CCC0(&D_004521E8);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFSMP *)pref->m_tag.m_pv)->smp = *psmp;
    return pref;
}
