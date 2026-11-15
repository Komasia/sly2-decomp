#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void *func_001F0380(void *plo, int a, int b, int carg); CRef func_00104840(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 368 (an SM's option 214): runs the state machine on an ALO from a state
   (object, state oid, grfapl) and returns the new SMA (0x1F0380). */
CRef func_00104840(void *psm, int carg, void *aref)
{
    int aotype[3] = {0x2030, OTYPE_Int, 0x100B};
    int palo, oidState, grfapl;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &palo, &oidState, &grfapl);
    ref = func_001F0380(psm, palo, oidState, grfapl);
    return ref;
}
