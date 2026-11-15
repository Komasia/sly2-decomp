/* BIF symbol?: is the argument a symbol? */
#include "splice.h"
CRef *RefOpIsSymbol__FiP4CRefP6CFrame(CRef *ret, int carg, CRef *aref)
{
    int tagk = aref->m_tagk;
    ret->m_tagk = TAGK_Bool;
    ret->m_tag.m_bool = tagk == TAGK_Symid;
    return ret;
}
