/* func_002035A8 (0x2035A8): PHOTOTARGET load (vt slot 13): the defaults, the XFM load, then an unset size takes the
 * radius and an unset list title the title. */
#include "h6_photo.h"

void LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(PHOTOTARGET *ptarget);

void func_002035A8(PHOTOTARGET *ptarget)
{
    ptarget->size = 0.0f;
    ptarget->radius = 75.0f;
    ptarget->tolerance = 0.25f;
    ptarget->radiusLinked = 5000.0f;
    LoadXfmFromBrx__FP3XFMP18CBinaryInputStream(ptarget);
    if (ptarget->size == 0.0f) ptarget->size = ptarget->radius;
    if (ptarget->listTitle == -2) ptarget->listTitle = ptarget->title;
}
