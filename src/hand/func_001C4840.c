/* func_001C4840 (0x1C4840): the world's current player PO. */
#include "po.h"

PO *func_001C4840(SW *psw)
{
    return psw->ppoCur;
}
