#include "m2c_prelude.h"
void func_00210268(void *arg0, void *arg1) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg1, s32 *, 0x40);
    if ((temp_v1 ^ 1) & 1) {
        M2C_FIELD(arg1, s32 *, 0x40) = (s32) M2C_FIELD(temp_v1, s32 *, 0);
        M2C_FIELD(temp_v1, s32 *, 0) = 0;
        M2C_FIELD(temp_v1, s32 *, 4) = 0;
        M2C_FIELD(arg0, s32 *, 0x3F18) = (s32) (M2C_FIELD(arg0, s32 *, 0x3F18) + 1);
    }
}
