#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00163838(void *plo, int, void *, int, int); CRef func_0010F030(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 1287: an object added in the task states of grf, removed in the others
   (0x163838). */
CRef func_0010F030(void *plo, int carg, void *aref)
{
    int aotype[4] = {OTYPE_Int, 0x9050, OTYPE_Int, 0xf};
    CRef v1;
    int v0;
    int v2;
    int v3;
    CRef ref = RefSetArgsFromSplice(4, aref, aotype, &v0, &v1, &v2, &v3);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00163838(plo, v0, &v1, v2, v3);
    return ref;
}
