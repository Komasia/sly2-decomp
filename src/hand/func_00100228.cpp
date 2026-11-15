#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, int *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
int FIsBasicDerivedFrom(void *plo, int n) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
CRef func_00100228(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 2 (every object's option 3): is the object derived from class n? (bool) */
CRef func_00100228(void *plo, int carg, void *aref)
{
    int otype = 7;
    int cid;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &cid);
    ref = FIsBasicDerivedFrom(plo, cid) != 0;
    return ref;
}
