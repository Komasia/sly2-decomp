#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00132DE0(void *plo, int n, qword q); CRef func_001006B8(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 9 (script + loader): sets the object's sidebag option n to the vector value
   (0x132DE0). */
CRef func_001006B8(void *plo, int carg, void *aref)
{
    int aotype[2] = {0x15, OTYPE_Vector};
    union { qword q; } value;
    int optid;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &optid, &value);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00132DE0(plo, optid, value.q);
    return ref;
}
