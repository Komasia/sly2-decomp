#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_00212828(void *plo, CRef *pref); CRef func_0010DE58(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 1132: the screen object's arguments list (+0xCC, 0x212828). */
CRef func_0010DE58(void *plo, int carg, void *aref)
{
    int otype = 0x8010;
    CRef r;
    CRef ref = RefSetArgsFromSplice(1, aref, &otype, &r);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_00212828(plo, &r);
    return ref;
}
