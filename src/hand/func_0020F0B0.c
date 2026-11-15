/* IsSwHandsOff (0x20F0B0; Sly 1 sw.c, same body, right after ResumeGame__FP9GAMEPAUSEi): whether the game is paused for the player
 * (EOPID 941). */
#include "sw.h"

int IsSwHandsOff__FP2SW(SW *psw)
{
    return psw->cHandsOff > 0;
}
