/* BIF matrix?: is the argument a matrix? */
#include "splice.h"
CRef *RefOpIsMatrix__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Matrix;
    return ret;
}
