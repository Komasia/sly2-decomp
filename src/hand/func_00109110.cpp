#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E1238(void *plo, qword, qword, float, float, int); CRef func_00109110(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 682: appends the vector command 0x38 (0x1E1238). */
CRef func_00109110(void *pscpt, int carg, void *aref)
{
    int aotype[5] = {OTYPE_Vector, OTYPE_Vector, OTYPE_Float, OTYPE_Float, 0x106d};
    union { qword q; } v0;
    union { qword q; } v1;
    float v2;
    float v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E1238(pscpt, v0.q, v1.q, v2, v3, v4);
    return ref;
}
