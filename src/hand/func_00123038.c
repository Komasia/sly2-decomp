/* RefOpMatrixDecomposeToTranslate (Sly 1 bif.cpp): the translation row of the argument matrix, as a vector. */
#include "splice.h"

CRef *func_001291E0(CRef *pref, struct VECTOR *pvector);   /* CRef(const VECTOR &): a vector reference to a copy */

CRef *RefOpMatrixDecomposeToTranslate__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    CRef ref;

    func_001291E0(&ref, (struct VECTOR *)aref[0].m_tag.m_pmatrix->mat[3]);
    __4CRefRC4CRef(pref, &ref);
    Decref__4CRef(&ref);
    return pref;
}
