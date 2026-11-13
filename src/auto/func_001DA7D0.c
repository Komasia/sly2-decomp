#include "m2c_prelude.h"
extern f32 D_002DDF0C;

void func_001DA7D0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x28) = -1;
    M2C_FIELD(arg0, f32 *, 0x2C) = (f32) D_002DDF0C;
    SetShopMsg__FP4SHOPii(arg0, -1, -1);
}
