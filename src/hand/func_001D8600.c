/* class: progress name table (LoadProgressFromBrx 0x1D7B88): allocate the pool for cname names (16 bytes each). */
#include "h3_progress.h"
struct MSG { int cb; int nKind; };
void *PvAllocSwImpl__Fi(struct MSG *pmsg);
static inline void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwImpl__Fi(pmsg); }

void func_001D8600(NAMETABLE *pnametable, int cname)
{
    struct MSG msg;
    pnametable->cnameFree = cname;
    pnametable->anamePool = PvAllocMsg(&msg, cname << 4, 0x10);
}
