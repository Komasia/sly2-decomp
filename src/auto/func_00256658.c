#include "m2c_prelude.h"
void func_00256658(s32 arg0) {
    void *temp_v0;
    void *var_s0;

    Free__9CDynArray(arg0 + 0x10);
    var_s0 = M2C_FIELD(arg0, void **, 0x28);
    if (var_s0 != NULL) {
        do {
            temp_v0 = M2C_FIELD(var_s0, void **, 8);
            M2C_FIELD(temp_v0, void (**)(void *), 0xC)(var_s0 + M2C_FIELD(temp_v0, s16 *, 8));
            var_s0 = M2C_FIELD(var_s0, void **, 4);
        } while (var_s0 != NULL);
    }
}
