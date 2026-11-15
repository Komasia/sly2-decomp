// LoadLaserFromBrx: loads a laser. Beams are added one at a time while the object's options run (AddLaserPair), so
// a scratch array for the maximum number of beams is taken from the stack heap first; after the SO load it is copied
// into a world allocation of the final size.
#include "h3_laser.h"
struct MSG { int cb; int nKind; };   // allocation request: size, alignment
class FRAME { public: int a[4]; FRAME(); ~FRAME(); };   // stack-heap frame (released on return)
struct LASER {
    char unk_so[0x198];   // the SO base
    int cpair;
    LASERPAIR *apair;
};
extern "C" void *PvAllocStackClearImpl(MSG *pmsg) asm("PvAllocStackClearImpl__Fi");
extern "C" void *PvAllocSwCopyImpl(MSG *pmsg, void *pv) asm("PvAllocSwCopyImpl__FiPv");
extern "C" void LoadSoFromBrx(LASER *plaser, void *pbis) asm("LoadSoFromBrx__FP2SOP18CBinaryInputStream");
static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocStackClearImpl(pmsg); }
static inline void *PvReallocMsg(MSG *pmsg, int cb, int nKind, void *pv) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwCopyImpl(pmsg, pv); }
// name: SafeHouse port (LoadLaserFromBrx)
extern "C" void LoadLaserFromBrx__FP2LOP18CBinaryInputStream(LASER *plaser, void *pbis)
{
    FRAME frame;
    MSG msg;
    plaser->apair = (LASERPAIR *)PvAllocMsg(&msg, CBEAM_LASER_MAX * sizeof(LASERPAIR), 0x10);
    LoadSoFromBrx(plaser, pbis);
    plaser->apair = (LASERPAIR *)PvReallocMsg(&msg, plaser->cpair * sizeof(LASERPAIR), 0x10, plaser->apair);
}
