/* SetEmitterAutoPause (Sly 1 emitter.c). */
#include "emitter.h"
#include "clock.h"

void SetEmitterAutoPause(EMITTER *pemitter, int fAutoPause)
{
    pemitter->fAutoPause = fAutoPause;
    pemitter->fValuesChanged = 1;
}
