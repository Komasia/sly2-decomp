#include "m2c_prelude.h"
void func_001732E0(void *arg0, s32 arg1) {
    s32 temp_a2;
    void *temp_v1;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0x50);
    if (temp_a2 < 0x80) {
        M2C_FIELD(arg0, s32 *, 0x50) = (s32) (temp_a2 + 1);
        temp_v1 = M2C_FIELD(arg0, s32 *, 0x54) + (temp_a2 * 0x1C);
        M2C_FIELD(temp_v1, s32 *, 4) = arg1;
        M2C_FIELD(temp_v1, s32 *, 0) = 0;
    }
}
