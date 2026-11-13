/* EndActorScriptAnim: an actor playing a script animation (FActorScriptAnim) is told to stop it (its virtual at vt
 * +0x2C0, with 0). */
#include "vtbl.h"

struct ACTOR {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
int FActorScriptAnim(struct ACTOR *pactor) asm("FActorScriptAnim__FP2LO");

// name: SafeHouse port (EndActorScriptAnim)
void EndActorScriptAnim__FP5ACTOR(struct ACTOR *pactor)
{
    if (FActorScriptAnim(pactor)) {
        VTENT *pvte = &pactor->pvt[0x2c0 / 8];
        ((void (*)(void *, int))pvte->pfn)(VT_THIS(pactor, pvte), 0);
    }
}
