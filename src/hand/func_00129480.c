/* CRef::CRef(CPair *): constructs a list reference to ppair and counts the new reference. */
#include "splice.h"
CRef *func_00129480(CRef *ret, CPair *ppair)
{
    ret->m_tag.m_ppair = ppair;
    ret->m_tagk = TAGK_Pair;
    ppair->cref++;
    return ret;
}
