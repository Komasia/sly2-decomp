/* CRef::SetLm: drops the old payload and makes the reference a fresh pooled copy of the range *plm. */
#include "splice_ref.h"
// name: SafeHouse port (CRef::SetLm)
CRef *SetLm__4CRefP2LM(CRef *pref, LM *plm)
{
    REFLM *p;
    Decref__4CRef(pref);
    pref->m_tagk = TAGK_Lm;
    p = (REFLM *)func_0011CCC0(&D_004521D0);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFLM *)pref->m_tag.m_pv)->lm = *plm;
    return pref;
}
