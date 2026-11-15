#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001DF908(void *plo, int, float, float, float, int, int, float, float, float, int); CRef func_001056A0(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 455: two (int, three floats, int) groups to 0x1DF908. */
CRef func_001056A0(void *plo, int carg, void *aref)
{
    int aotype[10] = {OTYPE_Int, OTYPE_Float, OTYPE_Float, OTYPE_Float, 0x100b, OTYPE_Int, OTYPE_Float, OTYPE_Float, OTYPE_Float, 0x100b};
    int v0;
    float v1;
    float v2;
    float v3;
    int v4;
    int v5;
    float v6;
    float v7;
    float v8;
    int v9;
    CRef ref = RefSetArgsFromSplice(10, aref, aotype, &v0, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8, &v9);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001DF908(plo, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9);
    return ref;
}
