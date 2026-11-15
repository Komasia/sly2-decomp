#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001E0310(void *plo, CRef *pref); CRef func_00106C08(void *plo, int carg, void *aref); }
/* SCPT command thunk, EOPID 628: appends script command 3 with an int list (at most 4) (0x1E0310). */
CRef func_00106C08(void *pscpt, int carg, void *aref)
{
    int otype = OTYPE_IntList;
    CRef refList;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &refList);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001E0310(pscpt, &refList);
    return ref;
}
