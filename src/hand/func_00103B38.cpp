#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_0020A058(void *plo, void *, void *); CRef func_00103B38(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 302 (a guard's option 426): two lists of at most 4 objects (0x20A058). */
CRef func_00103B38(void *plo, int carg, void *aref)
{
    int aotype[2] = {0xa002, 0xa002};
    CRef v0;
    CRef v1;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &v0, &v1);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_0020A058(plo, &v0, &v1);
    return ref;
}
