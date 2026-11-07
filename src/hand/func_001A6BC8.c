/* func_001A6BC8 (0x1A6BC8): LO virtual slot 38: move the LO to the world matrix of a transform node. */
#include "so.h"

void PlaceAloAt__FP3ALOP7MATRIX4(LO *plo, struct MATRIX4 *pmat);

void func_001A6BC8(LO *plo, XF *pxf)
{
    PlaceAloAt__FP3ALOP7MATRIX4(plo, &pxf->matWorld);
}
