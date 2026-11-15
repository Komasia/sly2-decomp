/* SetCmUFogMax__FP2CMf: sets the camera's uFogMax and recomputes the frustum (Sly 2's fog setters sit where Sly 1 has
 * SetCmSProgress and two unnamed setters, before SetCmRgbaFog). */
#include "cm.h"

// name: Sly 1 cm.c SetCmUFogMax (same body and place)
void SetCmUFogMax__FP2CMf(CM *pcm, float uFogMax)
{
    pcm->uFogMax = uFogMax;
    RecalcCmFrustrum__FP2CM(pcm);
}
