#include "m2c_prelude.h"
extern f32 D_002DDF0C;

void func_001DD7B8(void *arg0, s32 arg1) {
    if (arg1 != M2C_FIELD(arg0, s32 *, 0x28)) {
        M2C_FIELD(arg0, s32 *, 0x28) = arg1;
        M2C_FIELD(arg0, f32 *, 0x2C) = (f32) D_002DDF0C;
    }
}
