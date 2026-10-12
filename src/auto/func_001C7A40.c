#include "m2c_prelude.h"
s32 func_001C7A40(void *arg0) {
    s32 *temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s32 **, 0x244);
    var_v0 = -1;
    if (temp_v1 != NULL) {
        var_v0 = *temp_v1;
    }
    return var_v0;
}
