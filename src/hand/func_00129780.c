/* CRef::SetMatrix: drops the old payload and makes the reference a fresh pooled copy of *pmat. */
#include "splice_ref.h"
// name: SafeHouse port (CRef::SetMatrix)
CRef *SetMatrix__4CRefP7MATRIX4(CRef *pref, struct MATRIX4 *pmat)
{
    REFMATRIX *p;
    Decref__4CRef(pref);
    pref->m_tagk = TAGK_Matrix;
    p = (REFMATRIX *)func_0011CCC0(&D_004521A0);
    p->cref = 0;
    pref->m_tag.m_pv = p;
    p->cref++;
    ((REFMATRIX *)pref->m_tag.m_pv)->mat = *pmat;
    return pref;
}
