#include "m2c_prelude.h"
s32 func_00225A68(s32 arg0, s32 arg1) {
    s32 temp_v0;

    ClonePo__FP2POT0(arg0, arg1);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x1D0);
    if (temp_v0 == arg1) {
        M2C_FIELD(arg0, s32 *, 0x1D0) = arg0;
    }
    return temp_v0;
}
