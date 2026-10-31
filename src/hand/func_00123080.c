/* RefOpMatrixDecomposeToRotate (Sly 1 bif.cpp): in Sly 2 a plain copy of the argument matrix. */
#include "splice.h"

CRef *func_001292B0(CRef *pref, struct MATRIX4 *pmat);   /* CRef(const MATRIX4 &): a matrix reference to a copy */

CRef *RefOpMatrixDecomposeToRotate__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    CRef ref;

    func_001292B0(&ref, aref[0].m_tag.m_pmatrix);
    __4CRefRC4CRef(pref, &ref);
    Decref__4CRef(&ref);
    return pref;
}
