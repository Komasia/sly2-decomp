#include "m2c_prelude.h"
s32 func_00164030(s32);                             /* extern */

s32 func_00163400(void *arg0) {
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x68);
    var_v0 = 0;
    if (temp_a0 != 0) {
        var_v0 = func_00164030(temp_a0) != 0;
    }
    return var_v0;
}
