/* func_0014F630: SetCmNearClip, also in the active policy's saved value. */
#include "cm.h"

void func_0014F630(CM *pcm, float sNearClip)
{
    CPLCY *pcplcy;

    SetCmNearClip__FP2CMf(pcm, sNearClip);
    pcplcy = pcm->acpr[0].pcplcy;
    if (pcplcy != NULL) {
        pcplcy->sNearClipSaved = sNearClip;
    }
}
