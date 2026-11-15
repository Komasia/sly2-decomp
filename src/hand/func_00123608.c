/* BIF lm-check: is a number within a limit? */
#include "splice.h"
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
int FCheckLm(int n, float g) asm("FCheckLm__FP2LMf");
CRef *RefOpLmCheck__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int n = aref[0].m_tag.m_n;
    CRef ref;
    int f;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    f = FCheckLm(n, ref.m_tag.m_g) != 0;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = f;
    Decref__4CRef(&ref);
    return ret;
}
