/* BIF clq-evaluate: a quadratic at x. */
#include "splice.h"
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
CRef *RefOpClqEvaluate__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    float *a = (float *)aref[0].m_tag.m_pv;
    CRef ref;
    float t, g;
    RefCoerceF32__4CRef(&ref, &aref[1]);
    t = ref.m_tag.m_g;
    g = a[0] + t * (a[1] + t * a[2]);
    ret->m_tagk = TAGK_F32;
    ret->m_tag.m_g = g;
    Decref__4CRef(&ref);
    return ret;
}
