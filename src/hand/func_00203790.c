/* func_00203790 (0x203790): whether a photo target can be taken: it is in the world, its linked LO is not, and its
 * task (if any) is open (state 1). */
#include "h6_photo.h"
int func_00203790(PHOTOTARGET *ptarget)
{
    PHOTOTASK *ptask;
    if (!FPhotoTargetInWorld(ptarget)) return 0;
    if (ptarget->ploLinked && FPhotoTargetInWorld(ptarget->ploLinked)) return 0;
    ptask = ptarget->ptask;
    if (ptask && ptask->nState != 1) return 0;
    return 1;
}
