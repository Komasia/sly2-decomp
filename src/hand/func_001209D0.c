/* RefOpIsNullObj (Sly 1 bif.cpp): whether the argument is an object reference to no object. */
#include "splice.h"

CRef *RefOpIsNullObj__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    int fNull = 0;

    if (aref->m_tagk == TAGK_Basic) {
        fNull = aref->m_tag.m_pbasic == NULL;
    }
    pref->m_tag.m_bool = fNull;
    pref->m_tagk = TAGK_Bool;
    return pref;
}
