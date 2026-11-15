#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001F8A78(void *plo, int, int, qword); CRef RefXfhMovePos(void *plo, int carg, void *aref) asm("RefXfhMovePos__FP5BASICiP4CRef"); }
/* Splice method thunk, EOPID 1228: moves a transform handle to a world point (mode, priority, point). */
// name: SafeHouse port (RefXfhMovePos)
CRef RefXfhMovePos(void *plo, int carg, void *aref)
{
    int aotype[3] = {0x100d, 0x5, OTYPE_Vector};
    union { qword q; } pos;
    int mode;
    int priority;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &mode, &priority, &pos);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001F8A78(plo, mode, priority, pos.q);
    return ref;
}
