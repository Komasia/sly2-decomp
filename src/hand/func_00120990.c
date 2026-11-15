/* BIF null?: is the argument the empty list? */
#include "splice.h"
CRef *RefOpIsNull__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_None;
    return ret;
}
