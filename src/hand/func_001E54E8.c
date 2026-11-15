/* func_001E54E8: releases every effect the script holds on STEP actors, last first (ReleaseRunEffects). */
#include "relay.h"
void ReleaseRunEffects__FP3RUNP2LOii(JSG *pjsg, void *pstep, int nHold5, int nHold6);
void func_001E54E8(JSG *pjsg)
{
    while (pjsg->cstepHold) {
        ReleaseRunEffects__FP3RUNP2LOii(pjsg, pjsg->apstepHold[pjsg->cstepHold - 1], pjsg->anHold5[pjsg->cstepHold - 1], pjsg->anHold6[pjsg->cstepHold - 1]);
    }
}
