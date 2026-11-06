/* LeaveCritSect (Sly 1 thread.c): drop one nesting level; the last leave frees the section and signals its sema. */
#include "thread.h"

void SignalSema(int sema);

void LeaveCritSect__FP8CRITSECT(CRITSECT *pcritsect)
{
    int cEnter = pcritsect->cEnter - 1;
    pcritsect->cEnter = cEnter;
    if (cEnter == 0) {
        pcritsect->thread = -1;
        SignalSema(pcritsect->sema);
    }
}
