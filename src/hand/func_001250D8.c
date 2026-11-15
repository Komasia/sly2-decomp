/* BIF 127 convert-object-matrix: the matrix aref[2] taken from object aref[0]'s space to aref[1]'s. */
#include "splice.h"
typedef struct MATRIX4 MATRIX4;
void InitTag(CRef *pref, int tagk) asm("InitTag__4CRef");
void func_001A71B0(MATRIX4 *pmat, int a, int b, int c);
void Decref(CRef *pref) asm("Decref__4CRef");
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 127: a matrix from one object's space to another's)
CRef *RefOpConvertObjectMatrix__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    MATRIX4 mat;
    MATRIX4 *pmat;
    InitTag(&ref, TAGK_Matrix);
    pmat = (MATRIX4 *)ref.m_tag.m_pv;
    func_001A71B0(&mat, aref[0].m_tag.m_n, aref[1].m_tag.m_n, aref[2].m_tag.m_n);
    *pmat = mat;
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
