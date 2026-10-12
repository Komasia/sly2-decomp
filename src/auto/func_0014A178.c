#include "m2c_prelude.h"
void func_0014A178(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_a3;
    void *temp_v1;

    temp_a3 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_a3 < 0x100) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x58) + (temp_a3 * 0xC);
        M2C_FIELD(temp_v1, s32 *, 0) = arg1;
        M2C_FIELD(temp_v1, s32 *, 4) = arg2;
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) (M2C_FIELD(arg0, s32 *, 0x54) + 1);
    }
}
