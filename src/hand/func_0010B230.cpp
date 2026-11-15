#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00142310(void *plo, float, float, void *, float, float, qword, qword); CRef func_0010B230(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 760 (script + loader): the authored throw parameters (0x142310). */
CRef func_0010B230(void *plo, int carg, void *aref)
{
    int aotype[7] = {OTYPE_Float, OTYPE_Float, 0xa, OTYPE_Float, OTYPE_Float, OTYPE_Vector, OTYPE_Vector};
    union { qword q; } v2;
    union { qword q; } v5;
    union { qword q; } v6;
    float v0;
    float v1;
    float v3;
    float v4;
    CRef ref = RefSetArgsFromSplice(7, aref, aotype, &v0, &v1, &v2, &v3, &v4, &v5, &v6);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00142310(plo, v0, v1, &v2, v3, v4, v5.q, v6.q);
    return ref;
}
