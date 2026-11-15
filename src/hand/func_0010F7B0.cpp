#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
qword func_00155FB0(void *plo, qword q);
CRef func_0010F7B0(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 1341 (the boss's option 1156): where his missile from a point aims (0x155FB0). */
CRef func_0010F7B0(void *plo, int carg, void *aref)
{
    union { qword q; } u;
    int otype = OTYPE_Vector;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &u);
    ref = func_00155FB0(plo, u.q);
    return ref;
}
