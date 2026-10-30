/* func_001C40F8 (0x1C40F8): is this PO the one in focus (func_001C4A48: the override PO, else the current one)? */
#include "po.h"

PO *func_001C4A48(SW *psw);

int func_001C40F8(PO *ppo)
{
    return ppo == func_001C4A48(&D_003DD490);
}
