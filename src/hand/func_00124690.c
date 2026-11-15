/* BIF 118: the sound object as a reference. */
#include "splice.h"
void SetBasic__4CRefP5BASIC(CRef *pref, void *p);
extern char D_003DD040[];
CRef *func_00124690(CRef *ret)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    SetBasic__4CRefP5BASIC(&ref, D_003DD040);
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
