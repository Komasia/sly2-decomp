#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void *func_00156B98(void *plo, int a, qword q, int b); CRef func_0010BFF8(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 932: makes a fixed noise at a point (noise, point, the source) (0x156B98). */
CRef func_0010BFF8(void *plo, int carg, void *aref)
{
    int aotype[3] = {0x1046, OTYPE_Vector, 0x2002};
    union { qword q; } pos;
    int noise, ploSource;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &noise, &pos, &ploSource);
    ref = func_00156B98(plo, noise, pos.q, ploSource);
    return ref;
}
