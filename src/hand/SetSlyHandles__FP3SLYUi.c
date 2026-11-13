/* SetSlyHandles: Sly's seven handle controllers (CTRLSOURCE, +0x19E4..+0x19FC) added to or removed from their
 * records by the mask bits (bit 0x20 is the seventh, 0x40 the sixth); nothing without the first.
 * Layout: SafeHouse port (actor.h SLIDE aphandle). */
#include "ctrl.h"

struct SLY {
    /* 0x0000 */ char pad0[0x19e4];
    /* 0x19e4 */ CTRL *aphandle[7];   /* field: SafeHouse port */
};
void EnsureCtrlAdded__FP4CTRL(CTRL *pctrl);
void EnsureCtrlRemoved__FP4CTRL(CTRL *pctrl);

// name: SafeHouse port (SetSlyHandles)
void SetSlyHandles__FP3SLYUi(struct SLY *psly, unsigned int grf)
{
    CTRL *pctrl = psly->aphandle[0];
    if (pctrl != 0) {
        if (grf & 1)
            EnsureCtrlAdded__FP4CTRL(pctrl);
        else
            EnsureCtrlRemoved__FP4CTRL(pctrl);
        if (grf & 2)
            EnsureCtrlAdded__FP4CTRL(psly->aphandle[1]);
        else
            EnsureCtrlRemoved__FP4CTRL(psly->aphandle[1]);
        if (grf & 4)
            EnsureCtrlAdded__FP4CTRL(psly->aphandle[2]);
        else
            EnsureCtrlRemoved__FP4CTRL(psly->aphandle[2]);
        if (grf & 8)
            EnsureCtrlAdded__FP4CTRL(psly->aphandle[3]);
        else
            EnsureCtrlRemoved__FP4CTRL(psly->aphandle[3]);
        if (grf & 0x10)
            EnsureCtrlAdded__FP4CTRL(psly->aphandle[4]);
        else
            EnsureCtrlRemoved__FP4CTRL(psly->aphandle[4]);
        if (grf & 0x20)
            EnsureCtrlAdded__FP4CTRL(psly->aphandle[6]);
        else
            EnsureCtrlRemoved__FP4CTRL(psly->aphandle[6]);
        if (grf & 0x40) {
            EnsureCtrlAdded__FP4CTRL(psly->aphandle[5]);
            return;
        }
        EnsureCtrlRemoved__FP4CTRL(psly->aphandle[5]);
    }
}
