/* RefOpRadNormalize (Sly 1 bif.cpp): one of the unary float operations, through RefUfo. */
#include "splice.h"

CRef *RefUfo__FP4CRef4UFOK(CRef *pref, CRef *aref, int ufok);   /* applies s_mpufokpfnufo[ufok] to the argument */

CRef *RefOpRadNormalize__FiP4CRefP6CFrame(CRef *pref, int carg, CRef *aref, CFrame *pframe)
{
    RefUfo__FP4CRef4UFOK(pref, aref, UFOK_RadNormalize);
    return pref;
}
