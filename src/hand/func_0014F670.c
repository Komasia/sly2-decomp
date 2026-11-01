/* SetCmFarClip (Sly 1 cm.c; same body and place, after SetCmNearClip). */
#include "cm.h"

void SetCmFarClip__FP2CMf(CM *pcm, float sFarClip)
{
    pcm->sFarClip = sFarClip;
    RecalcCmFrustrum__FP2CM(pcm);
}
