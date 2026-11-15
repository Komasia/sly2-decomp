#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *a0) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
int FPointInShape(void *plo, qword q) asm("FPointInShape__FP2LOG9VU_VECTOR");
CRef func_00104718(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 366 (a shape's option 108): is the point inside the shape? (bool) */
CRef func_00104718(void *plo, int carg, void *aref)
{
    int aotype[1] = {OTYPE_Vector};
    union { qword q; } pos;
    CRef ref = RefSetArgsFromSplice(1, aref, aotype, &pos);
    ref = FPointInShape(plo, pos.q) != 0;
    return ref;
}
