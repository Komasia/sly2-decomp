/* func_0020F0C0: one more reason the game may not be paused; the first one tells the pad users (AddGrfusr). */
#include "sw.h"

void AddGrfusr__Fi(int grfusr);

void func_0020F0C0(SW *psw)
{
    if (++psw->cNoPause == 1) {
        AddGrfusr__Fi(4);   /* FUSR_NoPause */
    }
}
