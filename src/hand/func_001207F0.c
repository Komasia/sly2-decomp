/* RefOpEqual (Sly 1 bif.cpp): structural equality of its two arguments (RefEqualHelper recurses into lists). */
#include "splice.h"

CRef *RefEqualHelper__FP4CRefT0(CRef *pref, CRef *pref0, CRef *pref1);

CRef *RefOpEqual__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    RefEqualHelper__FP4CRefT0(pref, &aref[0], &aref[1]);
    return pref;
}
