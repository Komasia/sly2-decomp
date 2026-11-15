#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_0020AFF0(void *plo, int, float, float, float, float); CRef func_00104558(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 365 (script + loader): an int and four floats to 0x20AFF0. */
CRef func_00104558(void *plo, int carg, void *aref)
{
    int aotype[5] = {OTYPE_Int, OTYPE_Float, OTYPE_Float, OTYPE_Float, OTYPE_Float};
    int v0;
    float v1;
    float v2;
    float v3;
    float v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_0020AFF0(plo, v0, v1, v2, v3, v4);
    return ref;
}
