/* BIF print-sidebag: a no-op in the retail game (returns void). */
#include "splice.h"
CRef *RefOpPrintSidebag__FiP4CRefP6CFrame(CRef *ret)
{
    CRef ref;
    ref.m_tagk = TAGK_Nil;
    InitTag__4CRef(ret, TAGK_Void);
    Decref__4CRef(&ref);
    return ret;
}
