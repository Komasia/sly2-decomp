#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_0019EAA0(void *plo, qword a, qword b); CRef func_0010B340(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 766 (script + loader): two vectors to 0x19EAA0 on the object's +0xF50 member. */
CRef func_0010B340(void *plo, int carg, void *aref)
{
    int aotype[2] = {OTYPE_Vector, OTYPE_Vector};
    union { qword q; } u;
    union { qword q; } v;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &u, &v);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_0019EAA0((char *)plo + 0xF50, u.q, v.q);
    return ref;
}
