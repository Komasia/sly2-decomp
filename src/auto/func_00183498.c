#include "m2c_prelude.h"
s32 func_00183498(void *arg0, void *arg1) {
    M2C_FIELD(arg1, f32 *, 0) = (f32) (M2C_FIELD(arg0, f32 *, 0x10C) * -3.1415927f);
    M2C_FIELD(arg1, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 0x10C) * 3.1415927f);
    return 1;
}
