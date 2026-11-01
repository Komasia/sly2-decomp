/* SetCmMrdRatio (Sly 1 cm.c; the setter after SetCmRgbaFog). In Sly 2 it recomputes the frustrum of the camera it
 * is given (Sly 1 used g_pcm). */
#include "cm.h"

void SetCmMrdRatio__FP2CMf(CM *pcm, float ratio)
{
    pcm->rFovCullRef = ratio;
    RecalcCmFrustrum__FP2CM(pcm);
}
