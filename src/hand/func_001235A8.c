/* BIF lm-limit: clamps a number to a limit. */
#include "splice.h"
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
float GLimitLm(int n, float g) asm("GLimitLm__FP2LMf");
CRef *RefOpLmLimit__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int n = aref[0].m_tag.m_n;
    CRef ref;
    float g;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    g = GLimitLm(n, ref.m_tag.m_g);
    ret->m_tag.m_g = g;
    ret->m_tagk = TAGK_F32;
    Decref__4CRef(&ref);
    return ret;
}
