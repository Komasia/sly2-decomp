#include "m2c_prelude.h"
extern f32 g_clock;

// name: SafeHouse port (AddTargetrecGuard)
s32 AddTargetrecGuard__FP9TARGETRECP5GUARD(s32 arg0, s32 arg1) {
    s32 temp_v1;
    void *temp_v0;

    if (M2C_FIELD(arg0, s32 *, 0x28) == 0) {
        M2C_FIELD(arg0, f32 *, 0) = (f32) g_clock;
        SetTargetrecTimer__FP9TARGETRECi(arg0, 0);
    }
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x28);
    temp_v0 = arg0 + (temp_v1 * 4);
    M2C_FIELD(temp_v0, s32 *, 0x2C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (temp_v1 + 1);
    return (s32) temp_v0;
}
