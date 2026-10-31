/* func_00231440 (0x231440): XFM virtual slot 30: the XFM's world matrix, brought up to date first
 * (func_00231368). */
#include "so.h"

void func_00231368(XFM *pxfm);

struct MATRIX4 *func_00231440(XFM *pxfm)
{
    func_00231368(pxfm);
    return &pxfm->matWorld;
}
