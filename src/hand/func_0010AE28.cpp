#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00143090(void *plo, void *, void *, void *); CRef func_0010AE28(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 743: three 4-word arguments to 0x143090. */
CRef func_0010AE28(void *plo, int carg, void *aref)
{
    int aotype[3] = {0xa, 0xa, 0xa};
    union { qword q; } v0;
    union { qword q; } v1;
    union { qword q; } v2;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00143090(plo, &v0, &v1, &v2);
    return ref;
}
