/* func_002040F8 (0x2040F8): STEP virtual slot 84: 0 while STEP::nUnk204 is set, else 7. */
#include "step.h"

int func_002040F8(STEP *pstep)
{
    return (pstep->nUnk204 != 0) ? 0 : 7;
}
