/* func_00209BC0 (0x209BC0): the kind table entry that best fits the guard's current states. */
#include "stepguard.h"
struct KINDEM;
struct KINDEM *PkindeBest__FP5GUARDUl(struct GUARD *pguard, long grfState);
struct KINDEM *func_00209BC0(struct GUARD *pguard)
{
    return PkindeBest__FP5GUARDUl(pguard, pguard->grfState);
}
