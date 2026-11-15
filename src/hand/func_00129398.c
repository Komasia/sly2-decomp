/* CRef::CRef(LM *): constructs an lm (range) reference holding a fresh pooled copy of *plm. */
#include "splice_ref.h"
CRef *func_00129398(CRef *pref, LM *plm)
{
    REFLM *p;
    pref->m_tagk = TAGK_Lm;
    p = (REFLM *)func_0011CCC0(&D_004521D0);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFLM *)pref->m_tag.m_pv)->lm = *plm;
    return pref;
}
