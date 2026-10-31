/* RefOpNot (Sly 1 bif.cpp): true only for the boolean false. */
#include "splice.h"

CRef *RefOpNot__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    int fNot = 0;

    if (aref->m_tagk == TAGK_Bool) {
        fNot = aref->m_tag.m_bool == 0;
    }
    pref->m_tagk = TAGK_Bool;
    pref->m_tag.m_bool = fNot;
    return pref;
}
