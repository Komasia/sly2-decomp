/* CRef::CRef(VECTOR): constructs a vector reference holding a fresh pooled copy of vec. */
#include "splice_ref.h"
CRef *func_00129248(CRef *pref, qword vec)
{
    REFVECTOR *p;
    pref->m_tagk = TAGK_Vector;
    p = (REFVECTOR *)func_0011CCC0(&D_00452188);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFVECTOR *)pref->m_tag.m_pv)->vec = vec;
    return pref;
}
