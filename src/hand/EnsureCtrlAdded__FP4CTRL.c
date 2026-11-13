/* EnsureCtrlAdded: put a controller on its record's controller list unless it is already there. */
#include "ctrl.h"

int FXfHasCtrl(CTRL *pctrl) asm("FXfHasCtrl__FP2XF");   /* it takes the controller: whether it is on pctrl->pxf's list */
void AddXfCtrl(struct ALO *palo, struct XF *pxf, CTRL *pctrl) asm("AddXfCtrl__FP3ALOP2XFP4CTRL");

// name: SafeHouse port (EnsureCtrlAdded)
void EnsureCtrlAdded__FP4CTRL(CTRL *pctrl)
{
    if (!FXfHasCtrl(pctrl))
        AddXfCtrl(pctrl->palo, pctrl->pxf, pctrl);
}
