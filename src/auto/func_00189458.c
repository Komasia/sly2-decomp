#include "m2c_prelude.h"
s32 scePadGetState(s32, s32);                        /* extern */
s32 scePadGetState(s32, s32);                       /* extern */

s32 func_00189458(s32 arg0) {
    s32 temp_a1;
    s32 var_v0;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x18C0);
    var_v0 = 0;
    if (temp_a1 != 0) {
        FaceObject__FP5ACTORP2LO(arg0, temp_a1);
        var_v0 = 1;
    }
    return var_v0;
}
