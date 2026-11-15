#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001524D8(void *plo, int, int, int, int, int); CRef func_0010F838(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 1343: one dance move - its button, the good move (ASEG, grf), the bad, the
   missed (0x1524D8). */
CRef func_0010F838(void *plo, int carg, void *aref)
{
    int aotype[5] = {0x103c, OTYPE_Int, 0x100b, OTYPE_Int, OTYPE_Int};
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001524D8(plo, v0, v1, v2, v3, v4);
    return ref;
}
