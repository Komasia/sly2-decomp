/* func_00210100: hands out the next 12-byte record of the world array aUnk39d0. */
#include "sw.h"

SWREC12 *func_00210100(SW *psw)
{
    return &psw->aUnk39d0[psw->cUnk39d4++];
}
