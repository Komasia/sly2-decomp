/* CRef::SetClq: drops the old payload and makes the reference a fresh pooled copy of the quadratic *pclq. */
#include "splice_ref.h"
// name: SafeHouse port (CRef::SetClq)
CRef *SetClq__4CRefP3CLQ(CRef *pref, qword *pclq)
{
    REFCLQ *p;
    Decref__4CRef(pref);
    pref->m_tagk = TAGK_Clq;
    p = (REFCLQ *)func_0011CCC0(&D_004521B8);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFCLQ *)pref->m_tag.m_pv)->clq = *pclq;
    return pref;
}
