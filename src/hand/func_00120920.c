/* BIF lm?: is the argument a limit (LM)? */
#include "splice.h"
CRef *RefOpIsLm__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Lm;
    return ret;
}
