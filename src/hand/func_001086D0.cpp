#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E0E18(void *plo, int, int, int, int, int); CRef func_001086D0(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 668: appends script command 0x2A (0x1E0E18). */
CRef func_001086D0(void *pscpt, int carg, void *aref)
{
    int aotype[5] = {OTYPE_Int, 0x102e, 0x102f, OTYPE_Bool, OTYPE_Int};
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E0E18(pscpt, v0, v1, v2, v3, v4);
    return ref;
}
