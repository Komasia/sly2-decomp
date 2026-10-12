#include "m2c_prelude.h"
void func_00173318(void *arg0, s32 arg1) {
    s32 temp_a1;
    void *temp_v1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x50);
    if (temp_a1 < 0x80) {
        M2C_FIELD(arg0, s32 *, 0x50) = (s32) (temp_a1 + 1);
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x54) + (temp_a1 * 0x1C);
        M2C_FIELD(temp_v1, s32 *, 0) = 1;
        M2C_FIELD(temp_v1, s32 *, 4) = arg1;
    }
}
