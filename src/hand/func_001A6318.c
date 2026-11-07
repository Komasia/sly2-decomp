/* MatJtLo__FP2LO (0x1A6318): evaluate the LO's world matrix (virtual slot 30) for its side effects only. */
#include "so.h"

// name: SafeHouse port (MatJtLo)
void MatJtLo__FP2LO(LO *plo)
{
    VTE *pvte = &plo->pvt[31];   /* slot 30: world matrix */

    ((struct MATRIX4 *(*)(void *))pvte->pfn)((char *)plo + pvte->d);
}
