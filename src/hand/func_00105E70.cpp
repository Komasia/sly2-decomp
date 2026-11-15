#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" {
void func_00170BA0(void *plo, void *pv);
CRef func_00105E70(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 597 (script + loader): a 4-word range argument to 0x170BA0. */
CRef func_00105E70(void *plo, int carg, void *aref)
{
    union { qword q; } u;
    int otype = 0xA;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &u);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00170BA0(plo, &u);
    return ref;
}
