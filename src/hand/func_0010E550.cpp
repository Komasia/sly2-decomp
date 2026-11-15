#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
qword func_001E77B0(void *plo, qword q);
CRef func_0010E550(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 1223: a vector in, a vector out (0x1E77B0). */
CRef func_0010E550(void *plo, int carg, void *aref)
{
    union { qword q; } u;
    int otype = OTYPE_Vector;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &u);
    ref = func_001E77B0(plo, u.q);
    return ref;
}
