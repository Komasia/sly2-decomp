/* PosOfLo__FP2LO (0x1A62E8): world position of an LO: the translation row of its world matrix (virtual slot 30). */
#include "so.h"

// name: SafeHouse port (PosOfLo)
qword PosOfLo__FP2LO(LO *plo)
{
    VTENT *pvte = &plo->pvt[31];   /* slot 30: world matrix */
    struct MATRIX4 *pmat = ((struct MATRIX4 *(*)(void *))pvte->pfn)(VT_THIS(plo, pvte));

    return *(qword *)pmat->mat[3];
}
