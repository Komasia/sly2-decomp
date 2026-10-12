#include "m2c_prelude.h"
void func_001E0F18(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    void *temp_v0;

    temp_v0 = func_001E01F8(arg0, 0x2D, arg2);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg1;
    M2C_FIELD(temp_v0, f32 *, 0x14) = fparg0;
}
