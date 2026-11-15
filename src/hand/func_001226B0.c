/* BIF atan2. */
#include "splice.h"
float atan2f(float y, float x);
CRef *RefOpAtan2__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    float ag[2];
    int i;
    float g;
    for (i = 0; i < 2; i++) {
        CRef *p = &aref[i];
        if (p->m_tagk == TAGK_F32) ag[i] = p->m_tag.m_g; else ag[i] = p->m_tag.m_n;
    }
    g = atan2f(ag[0], ag[1]);
    ret->m_tag.m_g = g;
    ret->m_tagk = TAGK_F32;
    return ret;
}
