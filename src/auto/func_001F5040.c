#include "m2c_prelude.h"
s32 func_001F5040(void *arg0) {
    s32 temp_a0;
    s32 var_a1;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0xE8);
    var_a1 = 0;
    if ((temp_v1 == NULL) || ((temp_a0 = M2C_FIELD(temp_v1, s32 *, 0xC0), (temp_a0 == 3)) && (M2C_FIELD(temp_v1, s32 *, 0xA0) == temp_a0))) {
        var_a1 = 1;
    }
    return var_a1;
}
