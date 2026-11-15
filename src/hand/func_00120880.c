/* BIF integer?: is the argument an int? */
#include "splice.h"
CRef *RefOpIsInteger__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_S32;
    return ret;
}
