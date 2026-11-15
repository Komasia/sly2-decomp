#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E12E0(void *plo, qword, qword, float, int, int); CRef func_001091F0(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 683: appends the vector command 0x39 (0x1E12E0). */
CRef func_001091F0(void *pscpt, int carg, void *aref)
{
    int aotype[5] = {OTYPE_Vector, OTYPE_Vector, OTYPE_Float, OTYPE_Bool, OTYPE_Bool};
    union { qword q; } v0;
    union { qword q; } v1;
    float v2;
    int v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E12E0(pscpt, v0.q, v1.q, v2, v3, v4);
    return ref;
}
