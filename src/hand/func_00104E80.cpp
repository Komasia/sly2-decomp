#include "so.h"
#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { CRef func_00104E80(LO *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 405: the object's vtable slot 78 called with a target ALO (or nil) and a local
   point (the missiles' aim); no result. */
CRef func_00104E80(LO *plo, int carg, void *aref)
{
    int aotype[2] = {0x2030, OTYPE_Vector};
    union { qword q; } u;
    int n;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &n, &u);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    VTENT *pvte = &plo->pvt[78];
    ((void (*)(void *, int, void *))pvte->pfn)(VT_THIS(plo, pvte), n, &u);
    return ref;
}
