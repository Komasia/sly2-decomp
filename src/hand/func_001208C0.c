/* BIF vector?: is the argument a vector? */
#include "splice.h"
CRef *RefOpIsVector__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Vector;
    return ret;
}
