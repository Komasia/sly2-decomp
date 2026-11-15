/* CloneScptData (vt slot 41): clones a relay: the LO clone, then, when the script set its own command limit
 * (fCustomMax), the clone gets its own copy of the command array. */
#include "relay.h"
struct MSG { int cb; int nKind; };   /* allocation request: size, alignment */
void CloneLo__FP2LOT0(RELAY *prelay);
void *PvAllocSwCopyImpl__FiPv(struct MSG *pmsg, void *pv);
static inline void *PvReallocMsg(struct MSG *pmsg, int cb, int nKind, void *pv) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwCopyImpl__FiPv(pmsg, pv); }
// name: SafeHouse port (CloneScptData)
void CloneScptData__FP2LO(RELAY *prelay) {
    struct MSG msg;
    CloneLo__FP2LOT0(prelay);
    if (prelay->fCustomMax) prelay->arelaycmd = PvReallocMsg(&msg, prelay->crelaycmdMax * sizeof(RELAYCMD), 0x10, prelay->arelaycmd);
}
