/* BIF matrix-decompose-to-euler: the Euler angles of a matrix's rotation. */
#include "splice.h"
typedef int TI __attribute__((mode(TI)));
void func_00129248(CRef *pref, TI vec);
TI DecomposeEulerMatrix__FP7MATRIX3(int n);
CRef *RefOpMatrixDecomposeToEuler__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    func_00129248(&ref, DecomposeEulerMatrix__FP7MATRIX3(aref->m_tag.m_n));
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
