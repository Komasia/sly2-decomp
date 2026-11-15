/* BIF number?: is the argument an int or a float? */
#include "splice.h"
CRef *RefOpIsNum__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_S32 || tagk == TAGK_F32;
    return ret;
}
