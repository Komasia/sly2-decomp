/* BIF clq-evaluate-lm: a quadratic at x, limited. */
#include "splice.h"
typedef struct LM { float gMin; float gMax; } LM;
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
static __inline__ float GLimit(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
CRef *RefOpClqEvaluateLm__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    float *c = (float *)aref[0].m_tag.m_pv;
    LM *plm = (LM *)aref[1].m_tag.m_pv;
    CRef ref;
    float g;
    RefCoerceF32__4CRef(&ref, &aref[2]);
    g = ref.m_tag.m_g;
    ret->m_tag.m_g = GLimit(c[0] + g * (c[1] + g * c[2]), plm->gMin, plm->gMax);
    ret->m_tagk = TAGK_F32;
    Decref__4CRef(&ref);
    return ret;
}
