/* BIF are-near: are the first two numbers equal within the relative tolerance of the third (FFloatsNear)? */
#include "splice.h"
int FFloatsNear(float a, float b, float c) asm("FFloatsNear__Ffff");
CRef *RefOpAreNear__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    float ag[3];
    int i;
    int f;
    for (i = 0; i < 3; i++) {
        CRef *p = &aref[i];
        if (p->m_tagk == TAGK_S32) ag[i] = p->m_tag.m_n; else ag[i] = p->m_tag.m_g;
    }
    f = FFloatsNear(ag[0], ag[1], ag[2]) != 0;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = f;
    return ret;
}
