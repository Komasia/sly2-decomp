#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00185E30(void *plo, qword, qword, qword); CRef func_0010B618(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 771 (script + loader): Sly's three points of the surface (0x185E30). */
CRef func_0010B618(void *plo, int carg, void *aref)
{
    int aotype[3] = {OTYPE_Vector, OTYPE_Vector, OTYPE_Vector};
    union { qword q; } v0;
    union { qword q; } v1;
    union { qword q; } v2;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00185E30(plo, v0.q, v1.q, v2.q);
    return ref;
}
