#include "m2c_prelude.h"
s32 func_00178D00(s32);                             /* extern */

s32 func_0017DCB8(void *arg0) {
    s32 temp_s0;
    s32 var_v1;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x30);
    var_v1 = 0;
    if (temp_s0 == 1) {
        var_v1 = (func_00178D00(M2C_FIELD(arg0, s32 *, 0x18)) != 0) ? temp_s0 : 0;
    }
    return var_v1;
}
