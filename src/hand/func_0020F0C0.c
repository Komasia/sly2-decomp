/* PauseTalk__FP2SW: one more reason the game may not be paused; the first one tells the pad users (AddGrfusr). */
#include "sw.h"

void AddGrfusr__Fi(int grfusr);

// name: SafeHouse port (PauseTalk)
void PauseTalk__FP2SW(SW *psw)
{
    if (++psw->cNoPause == 1) {
        AddGrfusr__Fi(4);   /* FUSR_NoPause */
    }
}
