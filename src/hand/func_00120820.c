/* BIF boolean?: is the argument a bool? */
#include "splice.h"
CRef *RefOpIsBoolean__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Bool;
    return ret;
}
