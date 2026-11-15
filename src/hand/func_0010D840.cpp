#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void * func_00156698(void *plo, qword, int); CRef func_0010D840(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 1095 (a noise template's option 214): creates a noise at a point from a source
   and returns it (0x156698). */
CRef func_0010D840(void *pnoisetmpl, int carg, void *aref)
{
    int aotype[2] = {OTYPE_Vector, 0x2002};
    union { qword q; } pos;
    int ploSource;
    CRef ref = RefSetArgsFromSplice(2, aref, aotype, &pos, &ploSource);
    ref = func_00156698(pnoisetmpl, pos.q, ploSource);
    return ref;
}
