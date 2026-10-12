#include "m2c_prelude.h"
s32 func_00169988(void *arg0, void *arg1) {
    s32 var_v0;

    var_v0 = (s32) (M2C_FIELD(arg0, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4)) >> 6;
    if (var_v0 == 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8);
        if (var_v0 == 0) {
            var_v0 = (s32) (M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg1, s32 *, 0xC)) >> 6;
            if (var_v0 == 0) {
                return M2C_FIELD(arg0, s32 *, 0x10) - M2C_FIELD(arg1, s32 *, 0x10);
            }
        }
    }
    return var_v0;
}
