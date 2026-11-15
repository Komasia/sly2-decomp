#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00132CC8(void *plo, int n, void *pu); CRef func_001004A0(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 6 (script + loader): sets the object's sidebag option n to the value (0x132CC8),
   keeping the value's own kind. */
CRef func_001004A0(void *plo, int carg, void *aref)
{
    int aotype[2] = {0x15, 9};
    union { qword q; } value;
    int optid;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &optid, &value);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00132CC8(plo, optid, &value);
    return ref;
}
