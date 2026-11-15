#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void * func_001F03A8(void *plo, int, int, int, int); CRef func_001048F0(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 369: as EOPID 368 with one more argument (0x1F03A8). */
CRef func_001048F0(void *psm, int carg, void *aref)
{
    int aotype[4] = {0x2030, OTYPE_Int, 0x100b, 0x1054};
    int v0;
    int v1;
    int v2;
    int v3;
    CRef ref = RefSetArgsFromSplice(4, aref, aotype, &v0, &v1, &v2, &v3);
    ref = func_001F03A8(psm, v0, v1, v2, v3);
    return ref;
}
