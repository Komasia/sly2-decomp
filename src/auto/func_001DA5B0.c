#include "m2c_prelude.h"
s32 func_001DA5B0(void *arg0) {
    s32 var_v1;

    var_v1 = M2C_FIELD(arg0, s32 *, 0x20);
    if (var_v1 == -1) {
        var_v1 = M2C_FIELD(arg0, s32 *, 0x18);
    }
    return var_v1;
}
