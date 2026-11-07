/* ResumeTalk__FP2SW: one reason less for not pausing; the last one clears FUSR_NoPause (RemoveGrfusr). */
#include "sw.h"

void RemoveGrfusr__Fi(int grfusr);

// name: SafeHouse port (ResumeTalk)
void ResumeTalk__FP2SW(SW *psw)
{
    if (--psw->cNoPause == 0) {
        RemoveGrfusr__Fi(4);   /* FUSR_NoPause */
    }
}
