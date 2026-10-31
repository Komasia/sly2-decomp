/* RefOpCdr (Sly 1 bif.cpp): the rest of a list (the empty list after the last element). */
#include "splice.h"

CRef *func_00129480(CRef *pref, CPair *ppair);   /* CRef(CPair *): a pair reference, takes a reference on the pair */

CRef *RefOpCdr__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    CPair *ppairNext = aref->m_tag.m_ppair->m_ppairNext;

    if (ppairNext == NULL) {
        InitTag__4CRef(pref, TAGK_None);
    } else {
        func_00129480(pref, ppairNext);
    }
    return pref;
}
