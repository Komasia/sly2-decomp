/* UpdateGuard40 (class 0x40's update, the Ep4 Contessa): the step guards' update, then while walking (+0xF80 -1) on a
 * floor the heading frame is fitted to it (FitStepToFloor with the range D_002BD940 {-200, 200} and the three probe
 * positions D_002BD910). Layout: SafeHouse port (guard.h GUARD). */
#include "stepguard.h"
struct VECTOR;
extern float D_002BD940[2];           /* {-200, 200} */
extern struct VECTOR D_002BD910[3];   /* the probe positions */
void UpdateStepguard__FP9STEPGUARDf(struct GUARD *pguard, float dt);
void FitStepToFloor__FP3ALOP6VECTORiPG9VU_VECTOR(struct GUARD *pguard, float *pgRange, int cpos, struct VECTOR *apos);

// name: SafeHouse port (UpdateGuard40)
void UpdateGuard40__FP2LO(struct GUARD *pguard, float dt)
{
    UpdateStepguard__FP9STEPGUARDf(pguard, dt);
    if (pguard->kMove == -1 && pguard->step.pxpFloor)
        FitStepToFloor__FP3ALOP6VECTORiPG9VU_VECTOR(pguard, D_002BD940, 3, D_002BD910);
}
