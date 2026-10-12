#include "m2c_prelude.h"
void func_00187E08(void *arg0, s32 arg1) {
    s32 temp_a1;

    temp_a1 = ~arg1;
    M2C_FIELD(arg0, s32 *, 0x10B4) = (s32) (M2C_FIELD(arg0, s32 *, 0x10B4) & temp_a1);
    M2C_FIELD(arg0, s32 *, 0x10BC) = (s32) (M2C_FIELD(arg0, s32 *, 0x10BC) & temp_a1);
}
