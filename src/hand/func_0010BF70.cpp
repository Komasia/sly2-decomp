#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
void *PloNearestPlayer(void *plo, qword q) asm("PloNearestPlayer__FP6VECTORG9VU_VECTOR");
CRef func_0010BF70(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 929: the player nearest to a point. */
CRef func_0010BF70(void *plo, int carg, void *aref)
{
    union { qword q; } pos;
    int otype = OTYPE_Vector;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &pos);
    ref = PloNearestPlayer(plo, pos.q);
    return ref;
}
