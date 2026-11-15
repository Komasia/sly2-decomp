/* CRef::SetVector(VECTOR *): drops the old payload and makes the reference a fresh pooled copy of *pvec. */
#include "splice_ref.h"
CRef *func_001296A8(CRef *pref, qword *pvec)
{
    REFVECTOR *p;
    Decref__4CRef(pref);
    pref->m_tagk = TAGK_Vector;
    p = (REFVECTOR *)func_0011CCC0(&D_00452188);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFVECTOR *)pref->m_tag.m_pv)->vec = *pvec;
    return pref;
}
