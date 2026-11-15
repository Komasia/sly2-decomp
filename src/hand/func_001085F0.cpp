#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E0DB8(void *plo, int, float, float, int, int); CRef func_001085F0(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 667: appends script command 0x29 (0x1E0DB8). */
CRef func_001085F0(void *pscpt, int carg, void *aref)
{
    int aotype[5] = {OTYPE_Int, OTYPE_Float, OTYPE_Float, OTYPE_Bool, OTYPE_Int};
    int v0;
    float v1;
    float v2;
    int v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E0DB8(pscpt, v0, v1, v2, v3, v4);
    return ref;
}
