/* FActorScriptAnim: an actor is in a script animation when its state (the virtual at vt +0x2C8) is 5 or 6. */
#include "vtbl.h"

struct LO {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};

// name: SafeHouse port (FActorScriptAnim)
int FActorScriptAnim__FP2LO(struct LO *plo)
{
    VTENT *pvte = &plo->pvt[0x2c8 / 8];
    return (unsigned int)(((int (*)(void *))pvte->pfn)(VT_THIS(plo, pvte)) - 5) < 2;
}
