/* BIF 117 (find-player-object's world): the world object (SW) as a reference. */
#include "splice.h"
void SetBasic__4CRefP5BASIC(CRef *pref, void *p);
extern char g_sw[];
CRef *func_00124640(CRef *ret)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    SetBasic__4CRefP5BASIC(&ref, g_sw);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
