/* SetCmNearClipAll__FP2CMf: SetCmNearClip, also in the active policy's saved value. */
#include "cm.h"

// name: SafeHouse port (SetCmNearClipAll)
void SetCmNearClipAll__FP2CMf(CM *pcm, float sNearClip)
{
    CPLCY *pcplcy;

    SetCmNearClip__FP2CMf(pcm, sNearClip);
    pcplcy = pcm->acpr[0].pcplcy;
    if (pcplcy != NULL) {
        pcplcy->sNearClipSaved = sNearClip;
    }
}
