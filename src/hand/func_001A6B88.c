/* func_001A6B88 (0x1A6B88): LO virtual slot 37: match another object's transform - take its world matrix
 * (its virtual slot 30) and move this LO there (func_001A6BE8). */
#include "so.h"

void func_001A6BE8(LO *plo, struct MATRIX4 *pmat);

void func_001A6B88(LO *plo, LO *ploOther)
{
    VTE *pvte = &ploOther->pvt[31];   /* slot 30: world matrix */

    func_001A6BE8(plo, ((struct MATRIX4 *(*)(void *))pvte->pfn)((char *)ploOther + pvte->d));
}
