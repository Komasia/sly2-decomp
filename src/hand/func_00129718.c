/* CRef::SetVector (by value): drops the old payload and makes the reference a fresh pooled copy of vec. */
#include "splice_ref.h"
// name: SafeHouse port (CRef::SetVector)
CRef *SetVector__4CRefG9VU_VECTOR(CRef *pref, qword vec)
{
    REFVECTOR *p;
    Decref__4CRef(pref);
    pref->m_tagk = TAGK_Vector;
    p = (REFVECTOR *)func_0011CCC0(&D_00452188);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFVECTOR *)pref->m_tag.m_pv)->vec = vec;
    return pref;
}
