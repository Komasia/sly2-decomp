/* func_0020F1B8 (0x20F1B8): whether the guards are paused (SafeHouse ai.h FGamePausedForAi). */
#include "sw.h"

int func_0020F1B8(SW *psw)
{
    return psw->cPauseAi > 0;
}
