#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void SetGuardKinde__FP5GUARD3OIDii(void *plo, void *, int, int); CRef func_00102A88(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 243, loader version: an oid and two ints to SetGuardKinde (0x207B70). */
CRef func_00102A88(void *plo, int carg, void *aref)
{
    int aotype[3] = {0x9010, OTYPE_Int, 0x100b};
    CRef v0;
    int v1;
    int v2;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    SetGuardKinde__FP5GUARD3OIDii(plo, &v0, v1, v2);
    return ref;
}
