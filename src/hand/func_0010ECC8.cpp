#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00162728(void *plo, int, int, int, int, int); CRef func_0010ECC8(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 1256: an object's state-machine state for a task state (0x162728). */
CRef func_0010ECC8(void *plo, int carg, void *aref)
{
    int aotype[5] = {0x1050, OTYPE_Int, OTYPE_Int, OTYPE_Int, 0xf};
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00162728(plo, v0, v1, v2, v3, v4);
    return ref;
}
