/* BIF set-car! / set-cdr! (bifk 0x23 sets the car): stores the second argument into the pair's car, or links
 * the pair (or nil) as its cdr; returns void. */
#include "splice.h"
void __as__4CRefRC4CRef(CRef *pref, CRef *prefSrc);
void func_00256C58(void *p, void *q);
CRef *RefOpSetCadr__FiP4CRefP6CFrame4BIFK(CRef *ret, int carg, CRef *aref, int cref, int k)
{
    char *p = aref[0].m_tag.m_pv;
    if (k == 0x23)
        __as__4CRefRC4CRef((CRef *)(p + 8), &aref[1]);
    else if (aref[1].m_tagk == TAGK_Pair)
        func_00256C58(p + 0x10, aref[1].m_tag.m_pv);
    else
        func_00256C58(p + 0x10, 0);
    InitTag__4CRef(ret, TAGK_Void);
    return ret;
}
