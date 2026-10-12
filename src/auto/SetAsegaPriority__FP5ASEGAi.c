#include "m2c_prelude.h"
M2C_UNK func_002301D0(s32, s32);                    /* extern */

void SetAsegaPriority__FP5ASEGAi(void *arg0, s32 arg1) {
    void *var_s0;

    var_s0 = M2C_FIELD(arg0, void **, 0x34);
    if (var_s0 != NULL) {
        do {
            M2C_FIELD(var_s0, s32 *, 0xC) = arg1;
            func_002301D0(M2C_FIELD(var_s0, s32 *, 4), M2C_FIELD(var_s0, s32 *, 8));
            var_s0 = M2C_FIELD(var_s0, void **, 0x28);
        } while (var_s0 != NULL);
    }
}
