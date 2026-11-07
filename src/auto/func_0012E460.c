#include "m2c_prelude.h"
M2C_UNK EnsureCtrlRemoved__FP4CTRL(s32);                         /* extern */
M2C_UNK func_0012E210(s32);                         /* extern */

// name: SafeHouse port (DeleteCtrl)
void DeleteCtrl__FPP4CTRL(s32 *arg0) {
    s32 temp_s0;

    temp_s0 = *arg0;
    if (temp_s0 != 0) {
        EnsureCtrlRemoved__FP4CTRL(temp_s0);
        func_0012E210(temp_s0);
        *arg0 = 0;
    }
}
