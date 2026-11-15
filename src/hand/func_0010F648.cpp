#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001D7780(void *plo, CRef *pref); CRef func_0010F648(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 1339 (script + loader): the safe-house select's states, as an int list
   (0x1D7780). */
CRef func_0010F648(void *plo, int carg, void *aref)
{
    int otype = OTYPE_IntList;
    CRef refList;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &refList);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001D7780(plo, &refList);
    return ref;
}
