#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void SetGuardKind3__FP5GUARDiiiii(void *plo, void *, int, int, int, int); CRef func_00102C38(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 244, loader version: an oid and four ints to SetGuardKind3 (0x207C48). */
CRef func_00102C38(void *plo, int carg, void *aref)
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
    SetGuardKind3__FP5GUARDiiiii(plo, &v0, v1, v2, v3, v4);
    return ref;
}
