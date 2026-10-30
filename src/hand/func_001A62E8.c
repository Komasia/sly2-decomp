/* func_001A62E8 (0x1A62E8): world position of an LO: the translation row of its world matrix (virtual slot 30). */
#include "so.h"

qword func_001A62E8(LO *plo)
{
    VTE *pvte = &plo->pvt[31];   /* slot 30: world matrix */
    struct MATRIX4 *pmat = ((struct MATRIX4 *(*)(void *))pvte->pfn)((char *)plo + pvte->d);

    return *(qword *)pmat->mat[3];
}
