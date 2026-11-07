/* Deactivate__5CPLCYP2LOPv: CPLCY virtual slot 2: the policy is left; the camera gets back the near clip and target FOV kept
 * in the policy. */
#include "cm.h"

// name: SafeHouse port (CPLCY::Deactivate)
void Deactivate__5CPLCYP2LOPv(CPLCY *pcplcy)
{
    pcplcy->pvHero = NULL;
    SetCmNearClip__FP2CMf(&g_cm, pcplcy->sNearClipSaved);
    g_cm.fovTarget = pcplcy->gFovTargetSaved;
}
