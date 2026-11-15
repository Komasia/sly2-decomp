#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E1178(void *plo, int, int, int, int, float, float, float); CRef func_00108F80(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 680: appends script command 0x36 - four ints and three floats (0x1E1178). */
CRef func_00108F80(void *pscpt, int carg, void *aref)
{
    int aotype[7] = {0xe, OTYPE_Int, 0x5, 0x5, OTYPE_Float, OTYPE_Float, OTYPE_Float};
    int v0;
    int v1;
    int v2;
    int v3;
    float v4;
    float v5;
    float v6;
    CRef ref = RefSetArgsFromSplice(7, aref, aotype, &v0, &v1, &v2, &v3, &v4, &v5, &v6);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E1178(pscpt, v0, v1, v2, v3, v4, v5, v6);
    return ref;
}
