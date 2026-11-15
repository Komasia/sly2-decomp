#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { int NDetectState__FP8DETECTORP2LOi(void *plo, int, int); CRef func_00104188(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 347: a detector's state for an object (int). */
CRef func_00104188(void *pdetector, int carg, void *aref)
{
    int aotype[2] = {0x2002, 0x106b};
    int ploTarget;
    int n;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &ploTarget, &n);
    ref = NDetectState__FP8DETECTORP2LOi(pdetector, ploTarget, n);
    return ref;
}
