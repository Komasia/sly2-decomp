/* LoadLoFromBrx (0x1A5C28): LO virtual slot 13: read the LO's data from the level stream (LoadOptionsFromBrx__FPvP18CBinaryInputStream). */
#include "so.h"

void LoadOptionsFromBrx__FPvP18CBinaryInputStream(LO *plo, void *pbis);

void LoadLoFromBrx__FP2LOP18CBinaryInputStream(LO *plo, void *pbis)
{
    LoadOptionsFromBrx__FPvP18CBinaryInputStream(plo, pbis);
}
