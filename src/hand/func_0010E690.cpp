#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void func_001F8AD8(void *plo, int a, int b, void *ps); CRef RefXfhMoveRot(void *plo, int carg, void *aref) asm("RefXfhMoveRot__FP5BASICiP4CRef"); }
struct BIG { qword aq[4]; };
/* Splice method thunk, EOPID 1229: rotates a transform handle to a world rotation (mode, priority, matrix). */
// name: SafeHouse port (RefXfhMoveRot)
CRef RefXfhMoveRot(void *plo, int carg, void *aref)
{
    int aotype[3] = {0x100D, 5, 4};
    BIG mat;
    int mode, priority;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &mode, &priority, &mat);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    func_001F8AD8(plo, mode, priority, &mat);
    return ref;
}
