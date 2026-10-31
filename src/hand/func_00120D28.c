/* RefOpLength (Sly 1 bif.cpp): the number of elements of a list (0 for anything that is not a pair). */
#include "splice.h"

CRef *RefOpLength__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    int c = 0;
    CPair *ppair;

    if (aref->m_tagk == TAGK_Pair) {
        ppair = aref->m_tag.m_ppair;
        if (ppair != NULL) {
            do {
                ppair = ppair->m_ppairNext;
                c++;
            } while (ppair != NULL);
        }
    }
    pref->m_tag.m_n = c;
    pref->m_tagk = TAGK_S32;
    return pref;
}
