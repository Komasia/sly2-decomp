/* BIF float?: is the argument a float? */
#include "splice.h"
CRef *RefOpIsFloat__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_F32;
    return ret;
}
