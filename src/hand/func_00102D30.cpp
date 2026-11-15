#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00207CF8(void *plo, void *, int, int, int, int); CRef func_00102D30(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 244, live script version (0x207CF8). */
CRef func_00102D30(void *plo, int carg, void *aref)
{
    int aotype[5] = {0x9010, OTYPE_Int, OTYPE_Int, OTYPE_Int, OTYPE_Int};
    CRef v0;
    int v1;
    int v2;
    int v3;
    int v4;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00207CF8(plo, &v0, v1, v2, v3, v4);
    return ref;
}
