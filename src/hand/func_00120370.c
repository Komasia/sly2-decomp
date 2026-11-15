/* BIF: are the two integer arguments equal? (bool) */
#include "splice.h"
CRef *RefOpIntEqual__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int a = aref[0].m_tag.m_n;
    int b = aref[1].m_tag.m_n;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = a == b;
    return ret;
}
