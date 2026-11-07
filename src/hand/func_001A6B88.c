/* TeleportLo__FP2LOT0 (0x1A6B88): LO virtual slot 37: match another object's transform - take its world matrix
 * (its virtual slot 30) and move this LO there (PlaceAloAt__FP3ALOP7MATRIX4). */
#include "so.h"

void PlaceAloAt__FP3ALOP7MATRIX4(LO *plo, struct MATRIX4 *pmat);

// name: SafeHouse port (TeleportLo)
void TeleportLo__FP2LOT0(LO *plo, LO *ploOther)
{
    VTE *pvte = &ploOther->pvt[31];   /* slot 30: world matrix */

    PlaceAloAt__FP3ALOP7MATRIX4(plo, ((struct MATRIX4 *(*)(void *))pvte->pfn)((char *)ploOther + pvte->d));
}
