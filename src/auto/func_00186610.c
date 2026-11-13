#include "m2c_prelude.h"
s32 scePadGetState(s32, s32);                        /* extern */
s32 scePadGetState(s32, s32);                       /* extern */

s32 func_00186610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    func_0012CF88(arg0, arg1, arg2, arg3);
    temp_v0 = M2C_FIELD(arg0, void **, 8);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(temp_v0, s32 *, 0xA8);
    return (s32) temp_v0;
}
