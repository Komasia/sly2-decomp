/* SetRipgEmitb (Sly 1 rip.c): take the particle expansion from the emitter settings. */
#include "rip.h"
#include "emitter.h"

void SetRipgEmitb(RIPG *pripg, EMITB *pemitb)
{
    pripg->sExpand = pemitb->sExpand;
}
