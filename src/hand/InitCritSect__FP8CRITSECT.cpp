/* InitCritSect (Sly 1 thread.c). */
#include "thread.h"

int SemaCreate(int initCount, int maxCount);

void InitCritSect(CRITSECT *pcritsect)
{
    pcritsect->thread = -1;
    pcritsect->sema = SemaCreate(1, 1);
}
