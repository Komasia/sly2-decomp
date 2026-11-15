#include "splice_cref.h"
extern "C" CRef RefSetArgsFromSplice(int carg, void *aref, int *aotype, ...) asm("RefSetArgsFromSplice__FiP4CRefP4OTYPe");
extern "C" { void LaunchActorTo__FP5ACTORG9VU_VECTORff(void *plo, qword, float, float); CRef func_0010A790(void *plo, int carg, void *aref); }
/* Splice method thunk, EOPID 730: launches the actor to a point (elevation share, air time). */
CRef func_0010A790(void *plo, int carg, void *aref)
{
    int aotype[3] = {OTYPE_Vector, OTYPE_Float, OTYPE_Float};
    union { qword q; } v0;
    float v1;
    float v2;
    CRef ref = RefSetArgsFromSplice(3, aref, aotype, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(TAGK_Void);
    LaunchActorTo__FP5ACTORG9VU_VECTORff(plo, v0.q, v1, v2);
    return ref;
}
