/* SetCmFovTarget__FP2CMf: sets the camera's target FOV, also in the active policy's saved value. */
#include "cm.h"

// name: SafeHouse port (SetCmFovTarget)
void SetCmFovTarget__FP2CMf(CM *pcm, float fovTarget)
{
    CPLCY *pcplcy = pcm->acpr[0].pcplcy;

    pcm->fovTarget = fovTarget;
    if (pcplcy != NULL) {
        pcplcy->gFovTargetSaved = fovTarget;
    }
}
