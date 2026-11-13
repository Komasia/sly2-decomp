/* EnsureCtrlRemoved: take a controller off its record's controller list if it is there. */
#include "ctrl.h"

int FXfHasCtrl(CTRL *pctrl) asm("FXfHasCtrl__FP2XF");   /* it takes the controller: whether it is on pctrl->pxf's list */
void RemoveXfCtrl(struct ALO *palo, struct XF *pxf, CTRL *pctrl) asm("RemoveXfCtrl__FP3ALOP2XFP4CTRL");

// name: SafeHouse port (EnsureCtrlRemoved)
void EnsureCtrlRemoved__FP4CTRL(CTRL *pctrl)
{
    if (FXfHasCtrl(pctrl))
        RemoveXfCtrl(pctrl->palo, pctrl->pxf, pctrl);
}
