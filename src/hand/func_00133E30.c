/* FlushSwOxaDirty1: empties the world's dirty list 1 (SW +0x3D28): each attachment's object recomputes its bounds
 * (vt slot 49), which takes it off the list. Layout: SafeHouse port (so.h PHYSW, bbmark.cpp). */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; };
struct OXA { char pad[0x60]; struct LO *pso; };
struct SW { char pad[0x3d28]; struct OXA *poxaDirty1First; };
// name: SafeHouse port (FlushSwOxaDirty1)
void FlushSwOxaDirty1__FP2SW(struct SW *psw)
{
    struct OXA *poxa;
    while ((poxa = psw->poxaDirty1First) != 0) {
        struct LO *pso = poxa->pso;
        VTENT *vt = pso->vt;
        ((void (*)(void *))vt[49].pfn)(VT_THIS(pso, &vt[49]));
    }
}
