/* BIF add-option (BIFK 0x6C): RefOpObjectOption with that kind. */
#include "splice.h"
void RefOpObjectOption__FiP4CRefP6CFrame4BIFK(CRef *ret, void *pbasic, int cref, CRef *aref, int k);
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 108 = BIFK AddO, RefOpObjectOption 0x6C)
CRef *RefOpAddO__FiP4CRefP6CFrame(CRef *ret, void *pbasic, int cref, CRef *aref)
{
    RefOpObjectOption__FiP4CRefP6CFrame4BIFK(ret, pbasic, cref, aref, 0x6C);
    return ret;
}
