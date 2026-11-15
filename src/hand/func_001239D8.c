/* BIF modulo. */
#include "splice.h"
CRef *RefOpModulo__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int r = aref[0].m_tag.m_n % aref[1].m_tag.m_n;
    ret->m_tagk = TAGK_S32;
    ret->m_tag.m_n = r;
    return ret;
}
