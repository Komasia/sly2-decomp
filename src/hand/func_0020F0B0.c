/* IsSwHandsOff (Sly 1 sw.c; same body, right after the hands-off decrement ResumeGame__FP9GAMEPAUSEi): whether the player
 * currently has no control. */
#include "sw.h"

int IsSwHandsOff__FP2SW(SW *psw)
{
    return psw->cHandsOff > 0;
}
