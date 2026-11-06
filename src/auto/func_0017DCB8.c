#include "m2c_prelude.h"
s32 FArrived__9JOBFOLLOW(s32);                             /* extern */

// name: SafeHouse port (JOBGOTO::NArrived)
s32 NArrived__7JOBGOTO(void *arg0) {
    s32 temp_s0;
    s32 var_v1;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x30);
    var_v1 = 0;
    if (temp_s0 == 1) {
        var_v1 = (FArrived__9JOBFOLLOW(M2C_FIELD(arg0, s32 *, 0x18)) != 0) ? temp_s0 : 0;
    }
    return var_v1;
}
