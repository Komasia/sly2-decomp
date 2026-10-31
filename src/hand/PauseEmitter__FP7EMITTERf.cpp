/* PauseEmitter (0x15A138): stop emitting for dtPause seconds (Sly 1 emitter.c). */
#include "emitter.h"
#include "clock.h"

void PauseEmitter(EMITTER *pemitter, float dtPause)
{
    pemitter->tUnpause = g_clock.t + dtPause;
}
