/* func_001EFA90: Init (virtual slot 6) of SM (class 111, derived from LO; Sly 1 sm.c state machine): initialise the
 * LO part, then set bit 0x40 of the LO flags at +0x40. (Sly 1 has no InitSm; its SM used InitLo directly.) */
#include "so.h"

void InitLo__FP2LO(LO *plo);

int func_001EFA90(LO *plo)
{
    InitLo__FP2LO(plo);
    return plo->grfUnk40 |= 0x40;
}
