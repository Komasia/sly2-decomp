typedef int qword __attribute__((mode(TI)));
#include "clock.h"
#include "vtbl.h"
struct LO { char pad[0xC]; VTENT *vt; };
struct SOURCE { char pad[0x14]; int fBusy; float tUntil; };
struct SLOT { struct LO *plo; int pad; float tWait; struct SOURCE *psrc; int k; int pad2[3]; qword pos; };
struct SPAWNER { char pad[0x58]; int cUsed; char pad2[0xA0 - 0x5C]; float dtWaitFar; float dtUntilFar; };
qword PosCenter__Fv(struct SPAWNER *pspawner);
/* ReleaseSlot: free a spawner slot: kind 0 (the guard taken away: removed, vt slot 9) waits from now, kind 1 waits
 * dtWaitFar at the center; the source (unless f) is busy until now / now + dtUntilFar. */
// name: SafeHouse port (ReleaseSlot)
void ReleaseSlot__FP7SPAWNERP4SLOTii(struct SPAWNER *pspawner, struct SLOT *pslot, int k, int fKeepSource) {
    pslot->k = k;
    switch (k) {
    case 0:
        { struct LO *plo = pslot->plo; VTENT *pvte; pslot->tWait = g_clock.t; pvte = &plo->vt[9]; ((void (*)(void *))pvte->pfn)(VT_THIS(plo, pvte)); }
        if ((fKeepSource ^ 1) & 1) pslot->psrc->tUntil = g_clock.t;
        break;
    case 1:
        pslot->tWait = g_clock.t + pspawner->dtWaitFar;
        pslot->pos = PosCenter__Fv(pspawner);
        if ((fKeepSource ^ 1) & 1) pslot->psrc->tUntil = g_clock.t + pspawner->dtUntilFar;
        break;
    }
    pslot->plo = 0;
    pslot->psrc->fBusy = 0;
    pslot->psrc = 0;
    pspawner->cUsed--;
}
