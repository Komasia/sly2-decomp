#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void SetActorFollow__FP5ACTORiG9VU_VECTOR(void *plo, int n, qword q); CRef func_0010A940(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 733: the actor follows an object at an offset. */
CRef func_0010A940(void *plo, int carg, void *aref)
{
    int aotype[2] = {0x2002, OTYPE_Vector};
    union { qword q; } posOffset;
    int ploTarget;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &ploTarget, &posOffset);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    SetActorFollow__FP5ACTORiG9VU_VECTOR(plo, ploTarget, posOffset.q);
    return ref;
}
