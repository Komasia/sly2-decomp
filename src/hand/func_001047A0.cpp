#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *a0, void *a1) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
int func_00227D20(void *plo, qword q, float g);
CRef func_001047A0(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 367: a point and a float tested against the shape (bool, 0x227D20). */
CRef func_001047A0(void *plo, int carg, void *aref)
{
    int aotype[2] = {OTYPE_Vector, 0x16};
    union { qword q; } u;
    float g;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &u, &g);
    ref = func_00227D20(plo, u.q, g) != 0;
    return ref;
}
