/* RefOpMatrixCalculateDmat (Sly 1 bif.cpp): a new matrix computed from the two argument matrices by func_0011C3D0. */
#include "splice.h"

void func_0011C3D0(struct MATRIX4 *pmat0, struct MATRIX4 *pmat1, struct MATRIX4 *pmatOut);

CRef *RefOpMatrixCalculateDmat__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    CRef ref;

    InitTag__4CRef(&ref, TAGK_Matrix);
    func_0011C3D0(aref[0].m_tag.m_pmatrix, aref[1].m_tag.m_pmatrix, ref.m_tag.m_pmatrix);
    __4CRefRC4CRef(pref, &ref);
    Decref__4CRef(&ref);
    return pref;
}
