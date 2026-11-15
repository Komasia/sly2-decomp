/* class: progress (SafeHouse savedata.cpp PnProgressSlot: "0x1D7E80: the address of a path's value in the save"):
 * the address in the save pbSave of the value a path names: its node's ib plus index * the kind's size
 * (D_002C2D90[kind]). */
#include "h3_progress.h"
extern int D_002C2D90[];   /* byte size per PROGK */
void FFindEntryKey__FP4TRIEPP4PENTPi(LAYOUT *playout, KEY *pkey, PENTFOUND *pfound);

char *func_001D7E80(LAYOUT *playout, KEY *pkey, char *pbSave)
{
    PENTFOUND found;
    FFindEntryKey__FP4TRIEPP4PENTPi(playout, pkey, &found);
    return pbSave + (found.pent->ib + found.i * D_002C2D90[found.pent->kind]);
}
