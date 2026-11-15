/* CloneLaser: clones a laser: the SO clone, then the clone gets its own copy of the beam array. */
#include "h3_laser.h"
struct MSG { int cb; int nKind; };   /* allocation request: size, alignment */
typedef struct LASER { char unk_so[0x198]; int cpair; LASERPAIR *apair; } LASER;
void CloneSo__FP2SOT0(LASER *plaser);
void *PvAllocSwCopyImpl__FiPv(struct MSG *pmsg, void *pv);
static inline void *PvReallocMsg(struct MSG *pmsg, int cb, int nKind, void *pv) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwCopyImpl__FiPv(pmsg, pv); }
// name: SafeHouse port (CloneLaser)
void CloneLaser__FP3ALO(LASER *plaser) {
    struct MSG msg;
    CloneSo__FP2SOT0(plaser);
    plaser->apair = PvReallocMsg(&msg, plaser->cpair * sizeof(LASERPAIR), 0x10, plaser->apair);
}
