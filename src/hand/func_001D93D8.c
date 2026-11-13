/* The in-game HUD's widget list (SafeHouse hudwidget.h: module 0x1D93D8..0x1DFAD8, the list at 0x3D9E70): its init,
 * entries linked at +0x14. */
#include "so.h"
void InitDl__FP2DLi(DL *pdl, int ibDle);

DL *func_001D93D8(DL *pdl)
{
    InitDl__FP2DLi(pdl, 0x14);
    return pdl;
}
