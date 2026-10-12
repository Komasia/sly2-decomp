#include "m2c_prelude.h"
void func_00153810(void *arg0, s32 arg1, s32 arg2) {
    u32 temp_a0;
    void *temp_v0;

    temp_a0 = M2C_FIELD(arg0, u32 *, 0x2A8);
    if (temp_a0 < 0x80U) {
        M2C_FIELD(arg0, u32 *, 0x2A8) = (u32) (temp_a0 + 1);
        temp_v0 = arg0 + ((temp_a0 * 0x1C) + 0x2AC);
        M2C_FIELD(temp_v0, s32 *, 0) = arg1;
        M2C_FIELD(temp_v0, s32 *, 4) = arg2;
        M2C_FIELD(temp_v0, s32 *, 0xC) = -1;
    }
}
