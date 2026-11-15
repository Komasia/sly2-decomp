#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001D4C48(void *plo, int n, void *pu); CRef func_00110680(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 1421: an int and a 4-word argument to 0x1D4C48. */
CRef func_00110680(void *plo, int carg, void *aref)
{
    int aotype[2] = {OTYPE_Int, 0xa};
    union { qword q; } u;
    int n;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &n, &u);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001D4C48(plo, n, &u);
    return ref;
}
