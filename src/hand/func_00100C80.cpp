#include "so.h"
#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" CRef func_00100C80(LO *plo, int carg, void *aref);
/* Splice method thunk, EOPID 43: the object's vtable slot 73 asked about a point (bool). */
CRef func_00100C80(LO *plo, int carg, void *aref)
{
    union { qword q; } u;
    int otype = OTYPE_Vector;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &u);
    VTENT *pvt = &plo->pvt[73];
    ref = ((int (*)(void *, qword))pvt->pfn)(VT_THIS(plo, pvt), u.q) != 0;
    return ref;
}
