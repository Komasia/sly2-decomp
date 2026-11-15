#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E1488(void *plo, qword, qword, float); CRef func_001095E8(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 689: appends the vector command 0x3F (0x1E1488). */
CRef func_001095E8(void *pscpt, int carg, void *aref)
{
    int aotype[3] = {OTYPE_Vector, OTYPE_Vector, OTYPE_Float};
    union { qword q; } v0;
    union { qword q; } v1;
    float v2;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E1488(pscpt, v0.q, v1.q, v2);
    return ref;
}
