#include "m2c_prelude.h"
M2C_UNK EnsureCtrlAdded__FP4CTRL(s32);                         /* extern */
M2C_UNK EnsureCtrlRemoved__FP4CTRL(s32);                         /* extern */

// name: SafeHouse port (SetSlyHandles)
void SetSlyHandles__FP3SLYUi(void *arg0, s32 arg1) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x19E4);
    if (temp_a0 != 0) {
        if (arg1 & 1) {
            EnsureCtrlAdded__FP4CTRL(temp_a0);
        } else {
            EnsureCtrlRemoved__FP4CTRL(temp_a0);
        }
        if (arg1 & 2) {
            EnsureCtrlAdded__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19E8));
        } else {
            EnsureCtrlRemoved__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19E8));
        }
        if (arg1 & 4) {
            EnsureCtrlAdded__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19EC));
        } else {
            EnsureCtrlRemoved__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19EC));
        }
        if (arg1 & 8) {
            EnsureCtrlAdded__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19F0));
        } else {
            EnsureCtrlRemoved__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19F0));
        }
        if (arg1 & 0x10) {
            EnsureCtrlAdded__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19F4));
        } else {
            EnsureCtrlRemoved__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19F4));
        }
        if (arg1 & 0x20) {
            EnsureCtrlAdded__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19FC));
        } else {
            EnsureCtrlRemoved__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19FC));
        }
        if (arg1 & 0x40) {
            EnsureCtrlAdded__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19F8));
            return;
        }
        EnsureCtrlRemoved__FP4CTRL(M2C_FIELD(arg0, s32 *, 0x19F8));
    }
}
