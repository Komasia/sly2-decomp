/* BIF clq: builds a quadratic (CLQ) from three numbers. */
#include "splice.h"
void RefCoerceF32__4CRef(CRef *pref, CRef *prefSrc);
CRef *RefOpClq__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    int i;
    float *pg;
    InitTag__4CRef(&ref, TAGK_Clq);
    pg = (float *)ref.m_tag.m_pv;
    for (i = 0; i < 3; i++) {
        CRef tmp;
        RefCoerceF32__4CRef(&tmp, &aref[i]);
        pg[i] = tmp.m_tag.m_g;
        Decref__4CRef(&tmp);
    }
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
