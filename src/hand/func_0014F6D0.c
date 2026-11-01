/* func_0014F6D0: sets the camera's uFogMax and recomputes the frustum (Sly 2's fog setters sit where Sly 1 has
 * SetCmSProgress and two unnamed setters, before SetCmRgbaFog). */
#include "cm.h"

void func_0014F6D0(CM *pcm, float uFogMax)
{
    pcm->uFogMax = uFogMax;
    RecalcCmFrustrum__FP2CM(pcm);
}
