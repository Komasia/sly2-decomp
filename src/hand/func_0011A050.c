/* class: DL, a doubly-linked list (Sly 1 dl.c; same body as InitDl__FP2DLi at 0x11A1F8): its entry offset set.
 * Callers pass each list with the offset of the DLE inside its items. */
#include "so.h"

void func_0011A050(DL *pdl, int ibDle)
{
    pdl->ibDle = ibDle;
}
