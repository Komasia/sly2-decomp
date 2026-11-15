#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void * PasegaApplyAseg__Fiiiff(void *plo, int, float, float, int); CRef func_00101910(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 106 (an ASEG's option 214): applies the ASEG to an ALO (object, t, svt, grfapl)
   and returns the new ASEGA. */
CRef func_00101910(void *paseg, int carg, void *aref)
{
    int aotype[4] = {0x2030, OTYPE_Float, OTYPE_Float, 0x100b};
    int palo;
    float t;
    float svt;
    int grfapl;
    CRef ref = RefSetArgsFromSplice(4, aref, aotype, &palo, &t, &svt, &grfapl);
    ref = PasegaApplyAseg__Fiiiff(paseg, palo, t, svt, grfapl);
    return ref;
}
