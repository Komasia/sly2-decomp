/* BIF matrix-transpose. */
#include "splice.h"
typedef struct MATRIX4 MATRIX4;
void func_0011C1D8(MATRIX4 *pmat, int n);
void func_001292B0(CRef *pref, MATRIX4 *pmat);
CRef *RefOpMatrixTranspose__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    MATRIX4 mat;
    func_0011C1D8(&mat, aref->m_tag.m_n);
    func_001292B0(&ref, &mat);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
