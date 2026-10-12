#include "m2c_prelude.h"
s32 func_001E7FF0(void *arg0) {
    s32 var_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x17C);
    var_v0 = -1;
    if (temp_v1 != NULL) {
        var_v0 = M2C_FIELD(temp_v1, s32 *, 0x4C);
    }
    return var_v0;
}
