#include "m2c_prelude.h"
s32 FXfHasCtrl__FP2XF();                                /* extern */
M2C_UNK AddXfCtrl__FP3ALOP2XFP4CTRL(s32, s32, void *);            /* extern */

// name: SafeHouse port (EnsureCtrlAdded)
void EnsureCtrlAdded__FP4CTRL(void *arg0) {
    if (FXfHasCtrl__FP2XF() == 0) {
        AddXfCtrl__FP3ALOP2XFP4CTRL(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, s32 *, 8), arg0);
    }
}
