/* SetCmNearFog__FP2CMf: sets the camera's sNearFog and recomputes the frustum (Sly 2's fog setters sit where Sly 1 has
 * SetCmSProgress and two unnamed setters, before SetCmRgbaFog). */
#include "cm.h"

// name: Sly 1 cm.c SetCmNearFog (same body; Sly 1 order SetCmFarClip, SetCmNearFog, SetCmFarFog, SetCmUFogMax, SetCmRgbaFog kept)
void SetCmNearFog__FP2CMf(CM *pcm, float sNearFog)
{
    pcm->sNearFog = sNearFog;
    RecalcCmFrustrum__FP2CM(pcm);
}
