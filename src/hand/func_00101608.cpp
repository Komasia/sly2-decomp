#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001F82B8(void *plo, int, void *); CRef func_00101608(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 79 (script + loader): passes an int and a 4-word argument to 0x1F82B8 (the
   object's control record mode). */
CRef func_00101608(void *plo, int carg, void *aref)
{
    int aotype[2] = {0x104d, 0xa};
    union { qword q; } v1;
    int v0;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &v0, &v1);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001F82B8(plo, v0, &v1);
    return ref;
}
