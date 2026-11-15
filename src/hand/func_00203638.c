/* func_00203638 (0x203638): PHOTOTARGET post-load (vt slot 15): the LO post-load, then the target listens to its
 * task (AddLoListener). */
#include "h6_photo.h"

void PostLoLoad__FP2LO(PHOTOTARGET *ptarget);
void AddLoListener__FP2LOi(PHOTOTASK *ptask, PHOTOTARGET *ptarget);

void func_00203638(PHOTOTARGET *ptarget)
{
    PHOTOTASK *ptask;
    PostLoLoad__FP2LO(ptarget);
    ptask = ptarget->ptask;
    if (ptask != 0) {
        AddLoListener__FP2LOi(ptask, ptarget);
    }
}
