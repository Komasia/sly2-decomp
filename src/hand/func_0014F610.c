/* SetCmNearClip (Sly 1 cm.c; same body and place, between SetCmFov and SetCmFarClip). */
#include "cm.h"

void SetCmNearClip__FP2CMf(CM *pcm, float sNearClip)
{
    pcm->sNearClip = sNearClip;
    RecalcCmFrustrum__FP2CM(pcm);
}
