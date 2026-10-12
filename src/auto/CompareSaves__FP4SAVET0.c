#include "m2c_prelude.h"
s32 CompareSaves__FP4SAVET0(void *arg0, void *arg1) {
    s32 var_v0;

    var_v0 = M2C_FIELD(arg0, u16 *, 0x54) - M2C_FIELD(arg1, u16 *, 0x54);
    if (var_v0 == 0) {
        var_v0 = M2C_FIELD(arg0, u8 *, 0x52) - M2C_FIELD(arg1, u8 *, 0x52);
        if (var_v0 == 0) {
            var_v0 = M2C_FIELD(arg0, u8 *, 0x53) - M2C_FIELD(arg1, u8 *, 0x53);
            if (var_v0 == 0) {
                var_v0 = M2C_FIELD(arg0, u8 *, 0x56) - M2C_FIELD(arg1, u8 *, 0x56);
                if (var_v0 == 0) {
                    var_v0 = M2C_FIELD(arg0, u8 *, 0x57) - M2C_FIELD(arg1, u8 *, 0x57);
                    if (var_v0 == 0) {
                        return M2C_FIELD(arg0, u8 *, 0x58) - M2C_FIELD(arg1, u8 *, 0x58);
                    }
                }
            }
        }
    }
    return var_v0;
}
