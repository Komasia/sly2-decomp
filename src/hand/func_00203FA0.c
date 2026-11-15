/* func_00203FA0 (0x203FA0): STEP option setter (data-referenced): sets fNoContacts; turning it on forgets the floor
 * contact. */
#include "step.h"

void func_00203FA0(STEP *pstep, int fNoContacts)
{
    if (pstep->fNoContacts != fNoContacts) {
        pstep->fNoContacts = fNoContacts;
        if (fNoContacts != 0) {
            pstep->pxpFloor = 0;
        }
    }
}
