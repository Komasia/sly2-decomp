/* BIF clq?: is the argument a quadratic (CLQ)? */
#include "splice.h"
CRef *RefOpIsClq__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Clq;
    return ret;
}
