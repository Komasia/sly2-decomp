/* BIF 139: sets ThiefNet item a's acquired flag to b (0x1DAF38); returns void. */
#include "splice.h"
void func_001DAF38(int a, int b);
CRef *func_00125738(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    InitTag__4CRef(&ref, TAGK_Void);
    func_001DAF38(aref[0].m_tag.m_n, aref[1].m_tag.m_n);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
