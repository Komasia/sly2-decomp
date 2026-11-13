#include "m2c_prelude.h"
extern f32 g_clock;

void func_0015DCD8(s32 arg0) {
    void *temp_v0;

    UpdateLo__FP2LO(arg0);
    if ((g_clock - M2C_FIELD(arg0, f32 *, 0x68)) > (M2C_FIELD(arg0, f32 *, 0x5C) + M2C_FIELD(arg0, f32 *, 0x60) + M2C_FIELD(arg0, f32 *, 0x64))) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_v0, void (**)(s32), 0x4C)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x48));
    }
}
