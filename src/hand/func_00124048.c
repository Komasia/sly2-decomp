/* BIF get-option (BIFK 0x6F): RefOpObjectOption with that kind. */
#include "splice.h"
void RefOpObjectOption__FiP4CRefP6CFrame4BIFK(CRef *ret, void *pbasic, int cref, CRef *aref, int k);
// name: Sly 1 bif.cpp (BIF table g_mpbifkbif 0x2BBB90 entry 111 = BIFK GetO, RefOpObjectOption 0x6F)
CRef *RefOpGetO__FiP4CRefP6CFrame(CRef *ret, void *pbasic, int cref, CRef *aref)
{
    RefOpObjectOption__FiP4CRefP6CFrame4BIFK(ret, pbasic, cref, aref, 0x6F);
    return ret;
}
