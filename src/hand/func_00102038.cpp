#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void *PsndStartDialog__FP8SOUNDMGRii(void *plo, int a, int b); CRef func_00102038(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 137 (a sound manager method): starts dialog n and returns the sound. */
CRef func_00102038(void *psoundmgr, int carg, void *aref)
{
    int aotype[2] = {0x10, 0x105D};
    int dialog, n;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &dialog, &n);
    ref = PsndStartDialog__FP8SOUNDMGRii(psoundmgr, dialog, n);
    return ref;
}
