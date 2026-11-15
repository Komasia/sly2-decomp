#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, void *an) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" {
void func_0018DF58(void *plo, qword q);
CRef func_0010B6D0(void *plo, int carg, void *aref);
}
/* Splice method thunk, EOPID 772 (script + loader): Sly's hand offset below a hook (+0x1FA0, 0x18DF58). */
CRef func_0010B6D0(void *plo, int carg, void *aref)
{
    union { qword q; } u;
    int otype = OTYPE_Vector;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &u);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_0018DF58(plo, u.q);
    return ref;
}
