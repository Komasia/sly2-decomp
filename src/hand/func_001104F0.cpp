#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001D4B48(void *plo, int n, void *pu, float g); CRef func_001104F0(void *plo, int carg, void *aref); }
/* Splice loader-option thunk, EOPID 1419: an int, a float and a 4-word argument to 0x1D4B48. */
CRef func_001104F0(void *plo, int carg, void *aref)
{
    int aotype[3] = {OTYPE_Int, OTYPE_Float, 0xa};
    union { qword q; } u;
    int n;
    float g;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &n, &g, &u);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001D4B48(plo, n, &u, g);
    return ref;
}
