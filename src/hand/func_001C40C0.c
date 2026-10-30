/* func_001C40C0 (0x1C40C0): is this PO the world's current player (func_001C4840)? */
#include "po.h"

PO *func_001C4840(SW *psw);

int func_001C40C0(PO *ppo)
{
    return ppo == func_001C4840(&D_003DD490);
}
