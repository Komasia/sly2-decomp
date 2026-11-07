#include "m2c_prelude.h"
s32 FTaskDone__FP4TASK(s32);                             /* extern */

s32 func_00163400(void *arg0) {
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x68);
    var_v0 = 0;
    if (temp_a0 != 0) {
        var_v0 = FTaskDone__FP4TASK(temp_a0) != 0;
    }
    return var_v0;
}
