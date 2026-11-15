/* func_002040F8 (0x2040F8): STEP virtual slot 84: 0 while STEP::fNoContacts is set, else 7. */
#include "step.h"

int func_002040F8(STEP *pstep)
{
    return (pstep->fNoContacts != 0) ? 0 : 7;
}
