/* func_001A6BC8 (0x1A6BC8): LO virtual slot 38: move the LO to the world matrix of a transform node. */
#include "so.h"

void func_001A6BE8(LO *plo, struct MATRIX4 *pmat);

void func_001A6BC8(LO *plo, XF *pxf)
{
    func_001A6BE8(plo, &pxf->matWorld);
}
