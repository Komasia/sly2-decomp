#include "m2c_prelude.h"
s32 func_0021C820(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    func_0012CF88(arg0, arg1, arg2, arg3);
    temp_v0 = M2C_FIELD(arg3, s32 *, 0xA8);
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_v0;
    return temp_v0;
}
