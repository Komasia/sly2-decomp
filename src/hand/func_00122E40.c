/* RefOpMatrixInvert (Sly 1 bif.cpp): a new matrix holding the inverse of the argument. */
#include "splice.h"

void FInvertMatrix4__FP7MATRIX4T0(struct MATRIX4 *pmat, struct MATRIX4 *pmatInverse);

CRef *RefOpMatrixInvert__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    CRef ref;

    InitTag__4CRef(&ref, TAGK_Matrix);
    FInvertMatrix4__FP7MATRIX4T0(aref[0].m_tag.m_pmatrix, ref.m_tag.m_pmatrix);
    __4CRefRC4CRef(pref, &ref);
    Decref__4CRef(&ref);
    return pref;
}
