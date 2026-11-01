/* func_0014F6B0: sets the camera's sFarFog and recomputes the frustum (Sly 2's fog setters sit where Sly 1 has
 * SetCmSProgress and two unnamed setters, before SetCmRgbaFog). */
#include "cm.h"

void func_0014F6B0(CM *pcm, float sFarFog)
{
    pcm->sFarFog = sFarFog;
    RecalcCmFrustrum__FP2CM(pcm);
}
