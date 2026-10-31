/* RefOpGE (Sly 1 bif.cpp): numeric comparison of its two arguments through RefCmp. */
#include "splice.h"

CRef *RefCmp__FP4CRef4CMPK(CRef *pref, CRef *aref, int cmpk);

CRef *RefOpGE__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    RefCmp__FP4CRef4CMPK(pref, aref, CMPK_GE);
    return pref;
}
