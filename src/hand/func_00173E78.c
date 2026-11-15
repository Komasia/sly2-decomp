#include "clock.h"
extern float D_002BE5E0;
struct SLOT { int plo; float tTime; float tWait; int pad[9]; };
struct SPAWNER { char pad[0x5C]; int cslot; struct SLOT *aslot; };
/* PslotChoose: the slot to use for a spawn of kind k: the free slot waiting longest (past its wait), else (when
 * none) the longest-used slot of another kind older than D_002BE5E0. */
// name: SafeHouse port (PslotChoose)
struct SLOT *PslotChoose__FP7SPAWNERi(struct SPAWNER *pspawner, int k) {
    float t4 = g_clock.t - D_002BE5E0;
    float t8 = g_clock.t;
    struct SLOT *pslotBest = 0;
    struct SLOT *pslot;
    int i;
    for (i = 0; i < pspawner->cslot; i++) {
        pslot = &pspawner->aslot[i];
        if (pslot->plo != 0) {
            if (pslot->plo == k) continue;
            if (pslotBest && pslotBest->plo == 0) continue;
            if (t4 <= pslot->tTime) continue;
            t4 = pslot->tTime;
        } else {
            if (t8 <= pslot->tWait) continue;
            t8 = pslot->tWait;
        }
        pslotBest = pslot;
    }
    return pslotBest;
}
