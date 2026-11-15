/* BIF smp?: is the argument a smoothing parameter set (SMP)? */
#include "splice.h"
CRef *RefOpIsSmp__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Smp;
    return ret;
}
