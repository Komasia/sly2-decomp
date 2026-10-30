/* func_001A6BE8 (0x1A6BE8): move the LO to a world matrix: virtual slot 28 with its translation row, then
 * virtual slot 29 with the whole matrix (TranslateToPos / RotateToMat in Sly 1's vtable order). */
#include "so.h"

void func_001A6BE8(LO *plo, struct MATRIX4 *pmat)
{
    VTE *pvte;

    pvte = &plo->pvt[29];   /* slot 28: translate to position */
    ((void (*)(void *, qword))pvte->pfn)((char *)plo + pvte->d, *(qword *)pmat->mat[3]);
    pvte = &plo->pvt[30];   /* slot 29: rotate to matrix */
    ((void (*)(void *, struct MATRIX4 *))pvte->pfn)((char *)plo + pvte->d, pmat);
}
