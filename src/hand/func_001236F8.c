/* BIF abs (int or float). */
#include "splice.h"
void SetS32__4CRefi(CRef *pref, int n);
void SetF32__4CReff(CRef *pref, float g);
void Decref(CRef *pref) asm("Decref__4CRef");
CRef *RefOpAbs__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    if (aref->m_tagk == TAGK_S32) {
        int n = aref->m_tag.m_n;
        SetS32__4CRefi(&ref, n < 0 ? -n : n);
    } else {
        float g = *(float *)&aref->m_tag.m_n;
        if (g < 0.0f) g = -g;
        SetF32__4CReff(&ref, g);
    }
    __4CRefRC4CRef(ret, &ref);
    Decref(&ref);
    return ret;
}
