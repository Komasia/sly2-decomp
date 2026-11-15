#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff(void *plo, int, int, qword, qword, float, float); CRef func_00105BE0(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 535 (option 616): sets off the explosion with explicit parameters. */
CRef func_00105BE0(void *plo, int carg, void *aref)
{
    int aotype[6] = {0x1026, 0x2002, OTYPE_Vector, OTYPE_Vector, OTYPE_Float, OTYPE_Float};
    union { qword q; } v2;
    union { qword q; } v3;
    int v0;
    int v1;
    float v4;
    float v5;
    CRef ref = RefSetArgsFromSplice(6, aref, aotype, &v0, &v1, &v2, &v3, &v4, &v5);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff(plo, v0, v1, v2.q, v3.q, v4, v5);
    return ref;
}
