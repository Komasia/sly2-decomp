#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void * PasegaEnsureAseg(void *plo, int, int, float, float, int) asm("PasegaEnsureAseg__FP4ASEGP3ALO4SEEKffi"); CRef func_00101A88(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 108 (an ASEG's option 216): ensures the ASEG on an ALO (object, seek kind, t, svt,
   grfapl) and returns its ASEGA. */
CRef func_00101A88(void *paseg, int carg, void *aref)
{
    int aotype[5] = {0x2030, 0x100c, OTYPE_Float, OTYPE_Float, 0x100b};
    int palo;
    int seek;
    float t;
    float svt;
    int grfapl;
    CRef ref = RefSetArgsFromSplice(5, aref, aotype, &palo, &seek, &t, &svt, &grfapl);
    ref = PasegaEnsureAseg(paseg, palo, seek, t, svt, grfapl);
    return ref;
}
