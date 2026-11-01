/* func_0014FCE8: CPLCY virtual slot 2: the policy is left; the camera gets back the near clip and target FOV kept
 * in the policy. */
#include "cm.h"

void func_0014FCE8(CPLCY *pcplcy)
{
    pcplcy->pvHero = NULL;
    SetCmNearClip__FP2CMf(&g_cm, pcplcy->sNearClipSaved);
    g_cm.fovTarget = pcplcy->gFovTargetSaved;
}
