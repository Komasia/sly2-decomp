#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_0020A100(void *plo, int n, qword q); CRef func_00103F40(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 322: sets the guard's station - an object and a point in its frame (0x20A100). */
CRef func_00103F40(void *plo, int carg, void *aref)
{
    int aotype[2] = {0x2002, OTYPE_Vector};
    union { qword q; } posLocal;
    int ploStation;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &ploStation, &posLocal);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_0020A100(plo, ploStation, posLocal.q);
    return ref;
}
