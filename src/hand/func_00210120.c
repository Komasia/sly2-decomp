/* func_00210120: hands out the next 12-byte record of the world array aUnk39d8. */
#include "sw.h"

SWREC12 *func_00210120(SW *psw)
{
    return &psw->aUnk39d8[psw->cUnk39dc++];
}
