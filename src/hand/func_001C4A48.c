/* func_001C4A48 (0x1C4A48): the PO in focus: SW::ppoOverride when set, else the current player. */
#include "po.h"

PO *func_001C4A48(SW *psw)
{
    PO *ppo = psw->ppoOverride;

    if (ppo == NULL)
        ppo = psw->ppoCur;
    return ppo;
}
