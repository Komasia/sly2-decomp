/* BIF round. */
#include "splice.h"
CRef *RefOpRound__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    float g = aref->m_tag.m_g;
    ret->m_tagk = TAGK_S32;
    *(int *)&ret->m_tag.m_g = (int)(g + 0.5f);
    return ret;
}
