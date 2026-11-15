/* BIF object?: is the argument an object (BASIC)? */
#include "splice.h"
CRef *RefOpIsObject__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Basic;
    return ret;
}
