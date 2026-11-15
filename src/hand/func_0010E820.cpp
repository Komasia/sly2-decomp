#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001F8BF0(void *plo, int, float, float, float, float, qword); CRef func_0010E820(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 1231: a transform handle move with four floats and a point (0x1F8BF0). */
CRef func_0010E820(void *plo, int carg, void *aref)
{
    int aotype[6] = {0x5, OTYPE_Float, OTYPE_Float, OTYPE_Float, OTYPE_Float, OTYPE_Vector};
    union { qword q; } v5;
    int v0;
    float v1;
    float v2;
    float v3;
    float v4;
    CRef ref = RefSetArgsFromSplice(6, aref, aotype, &v0, &v1, &v2, &v3, &v4, &v5);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001F8BF0(plo, v0, v1, v2, v3, v4, v5.q);
    return ref;
}
