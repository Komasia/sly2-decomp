/* UnpauseEmitter: resume emitting (Sly 1 emitter.c). */
#include "emitter.h"
#include "clock.h"

void UnpauseEmitter(EMITTER *pemitter)
{
    pemitter->tUnpause = -1.0f;
}
