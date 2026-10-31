/* RefOpCar (Sly 1 bif.cpp): the first element of a list. */
#include "splice.h"

CRef *RefOpCar__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    __4CRefRC4CRef(pref, &aref->m_tag.m_ppair->m_ref);
    return pref;
}
