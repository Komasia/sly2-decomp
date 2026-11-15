/* One of the stub BIFs 140..168: returns nil. */
#include "splice.h"
CRef *func_00125DB0(CRef *ret)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    __4CRefRC4CRef(ret, &ref);
    Decref__4CRef(&ref);
    return ret;
}
