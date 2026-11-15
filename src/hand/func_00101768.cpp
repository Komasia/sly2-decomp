#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_0012EEE0(void *plo, int, int, int, float, float); CRef func_00101768(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 99: forwards three ints and two floats to 0x12EEE0. */
CRef func_00101768(void *plo, int carg, void *aref)
{
    int aotype[5] = {0xe, 0x5, 0x5, OTYPE_Float, OTYPE_Float};
    int v0;
    int v1;
    int v2;
    float v3;
    float v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_0012EEE0(plo, v0, v1, v2, v3, v4);
    return ref;
}
