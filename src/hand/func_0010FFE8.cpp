#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00181378(void *plo, int, void *, void *); CRef func_0010FFE8(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 1381 (script + loader): an enemy state's angle rule (0x181378). */
CRef func_0010FFE8(void *plo, int carg, void *aref)
{
    int aotype[3] = {0x105f, 0xa, 0xa};
    union { qword q; } v1;
    union { qword q; } v2;
    int v0;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00181378(plo, v0, &v1, &v2);
    return ref;
}
