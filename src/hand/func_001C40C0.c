/* func_001C40C0 (0x1C40C0): is this PO the world's current player (PloPlayerPo__FP2SW)? */
#include "po.h"

PO *PloPlayerPo__FP2SW(SW *psw);

int func_001C40C0(PO *ppo)
{
    return ppo == PloPlayerPo__FP2SW(&g_sw);
}
