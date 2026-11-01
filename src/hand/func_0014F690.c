/* func_0014F690: sets the camera's sNearFog and recomputes the frustum (Sly 2's fog setters sit where Sly 1 has
 * SetCmSProgress and two unnamed setters, before SetCmRgbaFog). */
#include "cm.h"

void func_0014F690(CM *pcm, float sNearFog)
{
    pcm->sNearFog = sNearFog;
    RecalcCmFrustrum__FP2CM(pcm);
}
