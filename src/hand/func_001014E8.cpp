#include "splice_cref.h"
extern "C" {
CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *a0, void *a1) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
void *func_001F8510(void *plo, int a, int b);
CRef RefXfHandle(void *plo, int carg, void *aref) asm("RefXfHandle__FP2LOiPv");
}
/* Splice method thunk, EOPID 77 (an ALO's option 194): the object's transform handle of the given kind
   (0x1F8510). */
// name: SafeHouse port (RefXfHandle)
CRef RefXfHandle(void *plo, int carg, void *aref)
{
    int aotype[2] = {OTYPE_Int, 0x104c};
    int k, kind;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &k, &kind);
    ref = func_001F8510(plo, k, kind);
    return ref;
}
