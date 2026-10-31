/* PauseEmitterIndefinite (0x15A150): stop emitting until UnpauseEmitter (Sly 1 emitter.c). */
#include "emitter.h"
#include "clock.h"

extern float D_002A514C;   /* "never" (Sly 1: DAT_0024a124) */

void PauseEmitterIndefinite(EMITTER *pemitter)
{
    pemitter->tUnpause = D_002A514C;
}
