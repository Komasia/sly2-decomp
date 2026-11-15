#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00207E08(void *plo, void *, int, float, float, float, float); CRef func_00102F38(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 245, live script version (0x207E08; resolved afterwards by 0x209130). */
CRef func_00102F38(void *plo, int carg, void *aref)
{
    int aotype[6] = {0x9010, OTYPE_Int, OTYPE_Float, OTYPE_Float, OTYPE_Float, OTYPE_Float};
    CRef v0;
    int v1;
    float v2;
    float v3;
    float v4;
    float v5;
    CRef ref = RefSetArgsFromSplice(6, aref, aotype, &v0, &v1, &v2, &v3, &v4, &v5);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00207E08(plo, &v0, v1, v2, v3, v4, v5);
    return ref;
}
