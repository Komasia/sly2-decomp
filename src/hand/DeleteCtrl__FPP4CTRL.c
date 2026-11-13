/* DeleteCtrl: a controller removed from its record's list, freed (0x12E210), and the pointer cleared.
 * Source: SafeHouse port (xf.cpp). */
#include "ctrl.h"

void EnsureCtrlRemoved__FP4CTRL(CTRL *pctrl);
void func_0012E210(CTRL *pctrl);   /* the controller deleted */

// name: SafeHouse port (DeleteCtrl)
void DeleteCtrl__FPP4CTRL(CTRL **ppctrl)
{
    CTRL *pctrl = *ppctrl;
    if (pctrl != 0) {
        EnsureCtrlRemoved__FP4CTRL(pctrl);
        func_0012E210(pctrl);
        *ppctrl = 0;
    }
}
