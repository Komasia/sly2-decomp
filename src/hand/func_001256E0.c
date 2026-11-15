/* BIF 138: is ThiefNet item n acquired? (bool) */
#include "splice.h"
void SetBool__4CRefi(CRef *pref, int f);
int FPowerupOwned__Fi(int n);
CRef *func_001256E0(CRef *ret, int carg, CRef *aref)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    SetBool__4CRefi(&ref, FPowerupOwned__Fi(aref->m_tag.m_n) != 0);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
