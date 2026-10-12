#include "m2c_prelude.h"
void func_00231220(void *arg0, void *arg1, void **arg2) {
    s32 temp_a0;
    void *temp_a1;
    void *temp_t0;
    void *var_a3;

    temp_t0 = *arg2;
    if (temp_t0 != NULL) {
        temp_a1 = M2C_FIELD(arg1, void **, 0x10);
        temp_a0 = (s32) (temp_t0 - M2C_FIELD(temp_a1, s32 *, 0x54)) >> 8;
        var_a3 = NULL;
        if ((temp_a0 >= 0) && (temp_a0 < M2C_FIELD(temp_a1, s32 *, 0x50))) {
            var_a3 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0x54) + (temp_a0 << 8);
        }
        if (M2C_FIELD(var_a3, void **, 0x88) == (temp_t0 + 0x80)) {
            M2C_FIELD(var_a3, void **, 0x88) = (void *) (var_a3 + 0x80);
        }
        if (M2C_FIELD(var_a3, s32 *, 0x8C) == (temp_t0 + 0x84)) {
            M2C_FIELD(var_a3, void **, 0x88) = (void *) (var_a3 + 0x84);
        }
        *arg2 = var_a3;
    }
}
