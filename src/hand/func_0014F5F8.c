/* func_0014F5F8: sets the camera's target FOV, also in the active policy's saved value. */
#include "cm.h"

void func_0014F5F8(CM *pcm, float fovTarget)
{
    CPLCY *pcplcy = pcm->acpr[0].pcplcy;

    pcm->fovTarget = fovTarget;
    if (pcplcy != NULL) {
        pcplcy->gFovTargetSaved = fovTarget;
    }
}
