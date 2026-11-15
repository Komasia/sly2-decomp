/* SetCmFarFog__FP2CMf: sets the camera's sFarFog and recomputes the frustum (Sly 2's fog setters sit where Sly 1 has
 * SetCmSProgress and two unnamed setters, before SetCmRgbaFog). */
#include "cm.h"

// name: Sly 1 cm.c SetCmFarFog (same body and place)
void SetCmFarFog__FP2CMf(CM *pcm, float sFarFog)
{
    pcm->sFarFog = sFarFog;
    RecalcCmFrustrum__FP2CM(pcm);
}
