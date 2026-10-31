/* PemitterEnsureEmitter (Sly 1 emitter.c): a caller about to change the emitter's settings marks them changed. */
#include "emitter.h"
#include "clock.h"

EMITTER *PemitterEnsureEmitter(EMITTER *pemitter, ENSK ensk)
{
    if (ensk == ENSK_Set)
        pemitter->fValuesChanged = 1;
    return pemitter;
}
